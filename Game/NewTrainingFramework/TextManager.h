#include <ft2build.h>
#include "../Utilities//Math.h"
#include "Globals.h"
#include FT_FREETYPE_H

class TextManager
{
public:
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;
	void Initialize();
	void RenderString(const char*, Vector4, float, float, float, float);

};