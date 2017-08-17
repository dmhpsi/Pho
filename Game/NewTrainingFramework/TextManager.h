#include <ft2build.h>
#include "../Utilities//Math.h"
#include "Globals.h"
#include "Shaders.h"
#include "ResourceManager.h"
#include FT_FREETYPE_H

class TextManager
{
private:
	static TextManager* Instance;
public:
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;
	Shaders* fontShader;
	GLuint fontId, vboId;
	void Initialize(const char*);
	void RenderString(char* text, Vector4 color, float x, float y, float scaleX, float scaleY);
	void RenderScore(int score, Vector4 color = Vector4(255,255,255), float x = -400, float y = 790, float scaleX = 1.8, float scaleY = 1.8);
	static TextManager* GetInstance();
	void CleanInstance();
};