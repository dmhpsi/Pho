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
	void RenderString(char*, Vector4, float, float, float, float);
	static TextManager* GetInstance();
	void CleanInstance();
};