#include "stdafx.h"
#include "TextManager.h"

TextManager* TextManager::Instance = 0;

TextManager* TextManager::GetInstance()
{
	if (Instance == 0)
	{
		Instance = new TextManager();
	}
	return Instance;
}

void TextManager::Initialize(const char *FileName)
{
	if (FT_Init_FreeType(&m_ft))
	{
		printf("Could not init freetype library\n");
		return;
	}
	if (FT_New_Face(m_ft, FileName, 0, &m_face))
	{
		printf("Could not open font\n");
		return;
	}
	else
	{
		printf("Finding font successfully \n");
	}
	FT_Set_Pixel_Sizes(m_face, 0, 48);
	m_glyphSlot = m_face->glyph;
	glGenTextures(1, &fontId);
	glBindTexture(GL_TEXTURE_2D, fontId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &vboId);
	return;
}

void TextManager::RenderString(char* text, Vector4 color, float x, float y, float scaleX, float scaleY)
{
	glUseProgram(fontShader->program);
	GLint uniform = glGetUniformLocation(fontShader->program, "u_color");
	//GLint uniSampler = glGetUniformLocation(fontShader->program, "u_s_texture");
	if (uniform != -1)
	{
		glUniform4f(uniform, color.x / 255, color.y / 255, color.z / 255, color.w);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindTexture(GL_TEXTURE_2D, fontId);

	float sx = 1.0f / Globals::screenWidth * scaleX;
	float sy = 1.0f / Globals::screenHeight * scaleY;

	x = x / Globals::screenWidth;
	y = y / Globals::screenHeight;

	for (const char *p = text; *p; p++)
	{
		if (FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
		{
			continue;
		}

		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			m_glyphSlot->bitmap.width,
			m_glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			m_glyphSlot->bitmap.buffer);


		float x2 = x + m_glyphSlot->bitmap_left * sx;
		float y2 = -y - m_glyphSlot->bitmap_top * sy;
		float w = m_glyphSlot->bitmap.width * sx;
		float h = m_glyphSlot->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{ x2,			-y2,			0,		0 },
			{ x2 + w,		-y2,			1,		0 },
			{ x2,			-y2 - h,		0,		1 },
			{ x2 + w,		-y2 - h,		1,		1 },
		};


		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		if (fontShader->positionAttribute != -1)
		{
			glEnableVertexAttribArray(fontShader->positionAttribute);
			glVertexAttribPointer(fontShader->positionAttribute, 4, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (m_glyphSlot->advance.x >> 6) * sx;
		y += (m_glyphSlot->advance.y >> 6) * sy;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextManager::RenderScore(int score, Vector4 color, float x, float y, float scaleX, float scaleY)
{
	char txtScores[20];
	sprintf(txtScores, "%d", score);
	RenderString(txtScores, color, x, y, scaleX, scaleY);
}

void TextManager::CleanInstance()
{
	delete Instance->fontShader;
	Instance->fontShader = NULL;
	delete Instance;
	Instance = NULL;
}