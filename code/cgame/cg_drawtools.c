/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
// cg_drawtools.c -- helper functions called by cg_draw, cg_scoreboard, cg_info, etc
#include "cg_local.h"


typedef struct OSP_ClientFont_t
{
	vmCvar_t* cvar;
	int modificationCount;
	int w;
	int h;
} OSP_ClientFont_t;

OSP_ClientFont_t OSP_ClientFontsTable[] =
{
	{&cf_Statusbar, -1, 0, 0},
	{&cf_Pickupstring, -1, 0, 0},
	{&cf_Teamchat, -1, 0, 0},
	{&cf_Teamoverlay, -1, 0, 0},
	{&cf_CrosshairNames, -1, 0, 0},
	{&cf_TeamCrosshairHealth, -1, 0, 0},
	{&cf_Vote, -1, 0, 0},
	{&cf_Following, -1, 0, 0},
	{&cf_AmmoStatusbar, -1, 0, 0},
	{&cf_Fragmsg, -1, 0, 0},
	{&cf_Scores, -1, 0, 0},
	{&cf_WeaponSwitch, -1, 0, 0},
	{&cf_WeaponName, -1, 0, 0},
};

const int OSP_ClientFontsTableSize = sizeof(OSP_ClientFontsTable) / sizeof(OSP_ClientFont_t);

/*
================
CG_OSPGetClientFontSize

Get custom font for specific command
================
*/
qboolean CG_OSPGetClientFontSize(const vmCvar_t* cvar, int* w, int* h)
{
	int i;
	const char* cvar_value;

	for (i = 0; i < OSP_ClientFontsTableSize; ++i)
	{
		if (OSP_ClientFontsTable[i].cvar != cvar) continue;
		if (OSP_ClientFontsTable[i].modificationCount != cvar->modificationCount)
		{
			int new_h = 0;
			int new_w = 0;
			cvar_value = cvar->string;

			while (*cvar_value >= '0' && *cvar_value <= '9')
			{
				new_w = new_w * 10 + (int)(*cvar_value - '0');
				++cvar_value;
			}

			if (*cvar_value != 'x' && *cvar_value != '*')
			{
				break;
			}
			++cvar_value;
			while (*cvar_value >= '0' && *cvar_value <= '9')
			{
				new_h = new_h * 10 + (int)(*cvar_value - '0');
				++cvar_value;
			}
			OSP_ClientFontsTable[i].w = new_w;
			OSP_ClientFontsTable[i].h = new_h;
		}
		*w = OSP_ClientFontsTable[i].w;
		*h = OSP_ClientFontsTable[i].h;
		OSP_ClientFontsTable[i].modificationCount = cvar->modificationCount;
		return qtrue;
	}
	/* default 16x16 */
	*w = 16;
	*h = 16;
	return qfalse;
}

/*
================
CG_CorrectWide

Adjust wide for wide screens
================
*/
void CG_CorrectWide(float* w)
{
}

/*
================
CG_AdjustFrom640

Adjusted for resolution and screen aspect ratio
================
*/
void CG_AdjustFrom640( float *x, float *y, float *w, float *h ) 
{
	// scale for screen sizes
	*x = *x * cgs.screenXScale + cgs.screenXBias;
	*y = *y * cgs.screenYScale + cgs.screenYBias;
	*w *= cgs.screenXScale;
	*h *= cgs.screenYScale;
}
void CG_AdjustFrom640_Old(float* x, float* y, float* w, float* h, qboolean correctWide)
{
#if 0
	// adjust for wide screens
	if (cgs.glconfig.vidWidth * 480 > cgs.glconfig.vidHeight * 640)
	{
		*x += 0.5 * (cgs.glconfig.vidWidth - (cgs.glconfig.vidHeight * 640 / 480));
	}
#endif
	// scale for screen sizes
	*x *= cgs.screenXScale_Old;
	*y *= cgs.screenYScale_Old;
	*h *= cgs.screenYScale_Old;

	if (!correctWide)
	{
		*w *= cgs.screenXScale_Old;
	}
	else
	{
		static qboolean koeffReady = qfalse;
		static float koeff;
		if (!koeffReady)
		{
			koeffReady = qtrue;
			koeff = cgs.screenXScale_Old * (cgs.glconfig.vidHeight * 640.0) / (cgs.glconfig.vidWidth * 480.0);
		}

		*w *= koeff;
	}
}

/*
================
CG_FillRect

Coordinates are 640*480 virtual values
=================
*/
void CG_FillRect(float x, float y, float width, float height, const float* color)
{
	trap_R_SetColor(color);

	CG_AdjustFrom640_Old(&x, &y, &width, &height, qfalse);
	trap_R_DrawStretchPic(x, y, width, height, 0, 0, 0, 0, cgs.media.whiteShader);

	trap_R_SetColor(NULL);
}

/*
================
CG_DrawSides

Coords are virtual 640x480
================
*/
void CG_DrawSides(float x, float y, float w, float h, float size)
{
	CG_AdjustFrom640_Old(&x, &y, &w, &h, qfalse);
	size *= cgs.screenXScale_Old;
	trap_R_DrawStretchPic(x, y, size, h, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_DrawStretchPic(x + w - size, y, size, h, 0, 0, 0, 0, cgs.media.whiteShader);
}

void CG_DrawTopBottom(float x, float y, float w, float h, float size)
{
	CG_AdjustFrom640_Old(&x, &y, &w, &h, qfalse);
	size *= cgs.screenYScale_Old;
	trap_R_DrawStretchPic(x, y, w, size, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_DrawStretchPic(x, y + h - size, w, size, 0, 0, 0, 0, cgs.media.whiteShader);
}
/*
================
UI_DrawRect

Coordinates are 640*480 virtual values
=================
*/
void CG_DrawRect(float x, float y, float width, float height, float size, const float* color)
{
	trap_R_SetColor(color);

	CG_DrawTopBottom(x, y, width, height, size);
	CG_DrawSides(x, y, width, height, size);

	trap_R_SetColor(NULL);
}



/*
================
CG_DrawPic

Coordinates are 640*480 virtual values
=================
*/
void CG_DrawPic(float x, float y, float width, float height, qhandle_t hShader)
{
	CG_AdjustFrom640_Old(&x, &y, &width, &height, qfalse);
	trap_R_DrawStretchPic(x, y, width, height, 0, 0, 1, 1, hShader);
}



/*
===============
CG_DrawChar

Coordinates and size in 640*480 virtual screen size
===============
*/
void CG_DrawChar(int x, int y, int width, int height, int ch)
{
	int row, col;
	float frow, fcol;
	float size;
	float   ax, ay, aw, ah;

	ch &= 255;

	if (ch == ' ')
	{
		return;
	}

	ax = x;
	ay = y;
	aw = width;
	ah = height;
	CG_AdjustFrom640_Old(&ax, &ay, &aw, &ah, qfalse);

	row = ch >> 4;
	col = ch & 15;

	frow = row * 0.0625;
	fcol = col * 0.0625;
	size = 0.0625;

	trap_R_DrawStretchPic(ax, ay, aw, ah,
	                      fcol, frow,
	                      fcol + size, frow + size,
	                      cgs.media.charsetShader);
}


/*
==================
CG_DrawStringExt

Draws a multi-colored string with a drop shadow, optionally forcing
to a fixed color.

Coordinates are at 640 by 480 virtual resolution
==================
*/
void CG_DrawStringExt(int x, int y, const char* string, const float* setColor,
                      qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars)
{
	vec4_t      color;
	const char*  s;
	int         xx;
	int         cnt;

	if (maxChars <= 0)
		maxChars = 32767; // do them all!

	// draw the drop shadow
	if (shadow)
	{
		color[0] = color[1] = color[2] = 0;
		color[3] = setColor[3];
		trap_R_SetColor(color);
		s = string;
		xx = x;
		cnt = 0;
		while (*s && cnt < maxChars)
		{
			if (Q_IsColorString(s))
			{
				s += 2;
				continue;
			}
			CG_DrawChar(xx + 2, y + 2, charWidth, charHeight, *s);
			cnt++;
			xx += charWidth;
			s++;
		}
	}

	// draw the colored text
	s = string;
	xx = x;
	cnt = 0;
	trap_R_SetColor(setColor);
	while (*s && cnt < maxChars)
	{
		if (Q_IsColorString(s))
		{
			if (!forceColor)
			{
				memcpy(color, g_color_table[ColorIndex(*(s + 1))], sizeof(color));
				color[3] = setColor[3];
				trap_R_SetColor(color);
			}
			s += 2;
			continue;
		}
		CG_DrawChar(xx, y, charWidth, charHeight, *s);
		xx += charWidth;
		cnt++;
		s++;
	}
	trap_R_SetColor(NULL);
}

void CG_DrawBigString(int x, int y, const char* s, float alpha)
{
	float   color[4];

	color[0] = color[1] = color[2] = 1.0;
	color[3] = alpha;
	CG_OSPDrawStringWithShadow(x, y, s, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, color, 0);
}

void CG_DrawBigStringColor(int x, int y, const char* s, vec4_t color)
{
	CG_DrawStringExt(x, y, s, color, qtrue, qtrue, BIGCHAR_WIDTH, BIGCHAR_HEIGHT, 0);
}

void CG_DrawSmallString(int x, int y, const char* s, float alpha)
{
	float   color[4];

	color[0] = color[1] = color[2] = 1.0;
	color[3] = alpha;
	CG_DrawStringExt(x, y, s, color, qfalse, qfalse, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0);
}

void CG_DrawSmallStringColor(int x, int y, const char* s, vec4_t color)
{
	CG_DrawStringExt(x, y, s, color, qtrue, qfalse, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0);
}

/*
=================
CG_DrawStrlen

Returns character count, skiping color escape codes
=================
*/
int CG_DrawStrlen(const char* str)
{
	int result = 0;
	float color;
	int len;

	if (!str) return 0;

	len = strlen(str);

	while (len && *str)
	{
		if (*str == '^')
		{
			++str; //skip ^
			--len;
			if (len)
			{
				if (*str == 'X' || *str == 'x')
				{
					++str; //skip code X/x
					--len;
					if (len >= 6 &&
					        CG_Hex16GetColor(&str[0], &color) &&
					        CG_Hex16GetColor(&str[2], &color) &&
					        CG_Hex16GetColor(&str[4], &color))
					{
						str += 6; //skip RRGGBB
						len -= 6;
						continue;
					}
				}
				else if (*str != '^')
				{
					++str; //skip code X/x
					--len;
					continue;
				}
			}
		}
		++str;
		--len;
		++result;
	}
	return result;
}

/*
=============
CG_TileClearBox

This repeats a 64*64 tile graphic to fill the screen around a sized down
refresh window.
=============
*/
static void CG_TileClearBox(int x, int y, int w, int h, qhandle_t hShader)
{
	float   s1, t1, s2, t2;

	s1 = x / 64.0;
	t1 = y / 64.0;
	s2 = (x + w) / 64.0;
	t2 = (y + h) / 64.0;
	trap_R_DrawStretchPic(x, y, w, h, s1, t1, s2, t2, hShader);
}



/*
==============
CG_TileClear

Clear around a sized down screen
==============
*/
void CG_TileClear(void)
{
	int     top, bottom, left, right;
	int     w, h;

	w = cgs.glconfig.vidWidth;
	h = cgs.glconfig.vidHeight;

	if (cg.refdef.x == 0 && cg.refdef.y == 0 &&
	        cg.refdef.width == w && cg.refdef.height == h)
	{
		return;     // full screen rendering
	}

	top = cg.refdef.y;
	bottom = top + cg.refdef.height - 1;
	left = cg.refdef.x;
	right = left + cg.refdef.width - 1;

	// clear above view screen
	CG_TileClearBox(0, 0, w, top, cgs.media.backTileShader);

	// clear below view screen
	CG_TileClearBox(0, bottom, w, h - bottom, cgs.media.backTileShader);

	// clear left of view screen
	CG_TileClearBox(0, top, left, bottom - top + 1, cgs.media.backTileShader);

	// clear right of view screen
	CG_TileClearBox(right, top, w - right, bottom - top + 1, cgs.media.backTileShader);
}



/*
================
CG_FadeColor
================
*/
float* CG_FadeColor(int startMsec, int totalMsec)
{
	static vec4_t       color;
	int         t;

	if (startMsec == 0)
	{
		return NULL;
	}

	t = cg.time - startMsec;

	if (t >= totalMsec)
	{
		return NULL;
	}

	// fade out
	if (totalMsec - t < FADE_TIME)
	{
		color[3] = (totalMsec - t) * 1.0 / FADE_TIME;
	}
	else
	{
		color[3] = 1.0;
	}
	color[0] = color[1] = color[2] = 1;

	return color;
}


/*
================
CG_TeamColor
================
*/
float* CG_TeamColor(int team)
{
	static vec4_t   red = {1, 0.2f, 0.2f, 1};
	static vec4_t   blue = {0.2f, 0.2f, 1, 1};
	static vec4_t   other = {1, 1, 1, 1};
	static vec4_t   spectator = {0.7f, 0.7f, 0.7f, 1};

	switch (team)
	{
		case TEAM_RED:
			return red;
		case TEAM_BLUE:
			return blue;
		case TEAM_SPECTATOR:
			return spectator;
		default:
			return other;
	}
}



/*
=================
CG_GetColorForHealth
=================
*/
void CG_GetColorForHealth(int health, int armor, vec4_t hcolor)
{
	int     count;
	int     max;

	// calculate the total points of damage that can
	// be sustained at the current health / armor level
	if (health <= 0)
	{
		VectorClear(hcolor);     // black
		hcolor[3] = 1;
		return;
	}
	count = armor;
	max = health * ARMOR_PROTECTION / (1.0 - ARMOR_PROTECTION);
	if (max < count)
	{
		count = max;
	}
	health += count;

	// set the color based on health
	hcolor[0] = 1.0;
	hcolor[3] = 1.0;
	if (health >= 100)
	{
		hcolor[2] = 1.0;
	}
	else if (health < 66)
	{
		hcolor[2] = 0;
	}
	else
	{
		hcolor[2] = (health - 66) / 33.0;
	}

	if (health > 60)
	{
		hcolor[1] = 1.0;
	}
	else if (health < 30)
	{
		hcolor[1] = 0;
	}
	else
	{
		hcolor[1] = (health - 30) / 30.0;
	}
}

/*
=================
CG_ColorForHealth
=================
*/
void CG_ColorForHealth(vec4_t hcolor)
{

	CG_GetColorForHealth(cg.snap->ps.stats[STAT_HEALTH],
	                     cg.snap->ps.stats[STAT_ARMOR], hcolor);
}



void CG_OSPDrawPoly(float x, float y, float w, float h, vec4_t color)
{
	trap_R_SetColor(color);
	CG_AdjustFrom640_Old(&x, &y, &w, &h, qfalse);
	trap_R_DrawStretchPic(x, y, w, h, 0, 0, 0, 0, cgs.media.whiteShader);
	trap_R_SetColor(colorWhite);
}


// bk001205 - code below duplicated in q3_ui/ui-atoms.c
// bk001205 - FIXME: does this belong in ui_shared.c?
// bk001205 - FIXME: HARD_LINKED flags not visible here
#ifndef Q3_STATIC // bk001205 - q_shared defines not visible here 
/*
=================
UI_DrawProportionalString2
=================
*/
static int  propMap[128][3] =
{
	{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},
	{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},

	{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},
	{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},

	{0, 0, PROP_SPACE_WIDTH},       // SPACE
	{11, 122, 7},   // !
	{154, 181, 14}, // "
	{55, 122, 17},  // #
	{79, 122, 18},  // $
	{101, 122, 23}, // %
	{153, 122, 18}, // &
	{9, 93, 7},     // '
	{207, 122, 8},  // (
	{230, 122, 9},  // )
	{177, 122, 18}, // *
	{30, 152, 18},  // +
	{85, 181, 7},   // ,
	{34, 93, 11},   // -
	{110, 181, 6},  // .
	{130, 152, 14}, // /

	{22, 64, 17},   // 0
	{41, 64, 12},   // 1
	{58, 64, 17},   // 2
	{78, 64, 18},   // 3
	{98, 64, 19},   // 4
	{120, 64, 18},  // 5
	{141, 64, 18},  // 6
	{204, 64, 16},  // 7
	{162, 64, 17},  // 8
	{182, 64, 18},  // 9
	{59, 181, 7},   // :
	{35, 181, 7},   // ;
	{203, 152, 14}, // <
	{56, 93, 14},   // =
	{228, 152, 14}, // >
	{177, 181, 18}, // ?

	{28, 122, 22},  // @
	{5, 4, 18},     // A
	{27, 4, 18},    // B
	{48, 4, 18},    // C
	{69, 4, 17},    // D
	{90, 4, 13},    // E
	{106, 4, 13},   // F
	{121, 4, 18},   // G
	{143, 4, 17},   // H
	{164, 4, 8},    // I
	{175, 4, 16},   // J
	{195, 4, 18},   // K
	{216, 4, 12},   // L
	{230, 4, 23},   // M
	{6, 34, 18},    // N
	{27, 34, 18},   // O

	{48, 34, 18},   // P
	{68, 34, 18},   // Q
	{90, 34, 17},   // R
	{110, 34, 18},  // S
	{130, 34, 14},  // T
	{146, 34, 18},  // U
	{166, 34, 19},  // V
	{185, 34, 29},  // W
	{215, 34, 18},  // X
	{234, 34, 18},  // Y
	{5, 64, 14},    // Z
	{60, 152, 7},   // [
	{106, 151, 13}, // '\'
	{83, 152, 7},   // ]
	{128, 122, 17}, // ^
	{4, 152, 21},   // _

	{134, 181, 5},  // '
	{5, 4, 18},     // A
	{27, 4, 18},    // B
	{48, 4, 18},    // C
	{69, 4, 17},    // D
	{90, 4, 13},    // E
	{106, 4, 13},   // F
	{121, 4, 18},   // G
	{143, 4, 17},   // H
	{164, 4, 8},    // I
	{175, 4, 16},   // J
	{195, 4, 18},   // K
	{216, 4, 12},   // L
	{230, 4, 23},   // M
	{6, 34, 18},    // N
	{27, 34, 18},   // O

	{48, 34, 18},   // P
	{68, 34, 18},   // Q
	{90, 34, 17},   // R
	{110, 34, 18},  // S
	{130, 34, 14},  // T
	{146, 34, 18},  // U
	{166, 34, 19},  // V
	{185, 34, 29},  // W
	{215, 34, 18},  // X
	{234, 34, 18},  // Y
	{5, 64, 14},    // Z
	{153, 152, 13}, // {
	{11, 181, 5},   // |
	{180, 152, 13}, // }
	{79, 93, 17},   // ~
	{0, 0, -1}      // DEL
};

static int propMapB[26][3] =
{
	{11, 12, 33},
	{49, 12, 31},
	{85, 12, 31},
	{120, 12, 30},
	{156, 12, 21},
	{183, 12, 21},
	{207, 12, 32},

	{13, 55, 30},
	{49, 55, 13},
	{66, 55, 29},
	{101, 55, 31},
	{135, 55, 21},
	{158, 55, 40},
	{204, 55, 32},

	{12, 97, 31},
	{48, 97, 31},
	{82, 97, 30},
	{118, 97, 30},
	{153, 97, 30},
	{185, 97, 25},
	{213, 97, 30},

	{11, 139, 32},
	{42, 139, 51},
	{93, 139, 32},
	{126, 139, 31},
	{158, 139, 25},
};

#define PROPB_GAP_WIDTH     4
#define PROPB_SPACE_WIDTH   12
#define PROPB_HEIGHT        36

/*
=================
UI_DrawBannerString
=================
*/
static void UI_DrawBannerString2(int x, int y, const char* str, vec4_t color)
{
	const char* s;
	unsigned char   ch; // bk001204 : array subscript
	float   ax;
	float   ay;
	float   aw;
	float   ah;
	float   frow;
	float   fcol;
	float   fwidth;
	float   fheight;

	// draw the colored text
	trap_R_SetColor(color);

	ax = x * cgs.screenXScale_Old + cgs.screenXBias_Old;
	ay = y * cgs.screenXScale_Old;

	s = str;
	while (*s)
	{
		ch = *s & 127;
		if (ch == ' ')
		{
			ax += ((float)PROPB_SPACE_WIDTH + (float)PROPB_GAP_WIDTH) * cgs.screenXScale_Old;
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			ch -= 'A';
			fcol = (float)propMapB[ch][0] / 256.0f;
			frow = (float)propMapB[ch][1] / 256.0f;
			fwidth = (float)propMapB[ch][2] / 256.0f;
			fheight = (float)PROPB_HEIGHT / 256.0f;
			aw = (float)propMapB[ch][2] * cgs.screenXScale_Old;
			ah = (float)PROPB_HEIGHT * cgs.screenXScale_Old;
			trap_R_DrawStretchPic(ax, ay, aw, ah, fcol, frow, fcol + fwidth, frow + fheight, cgs.media.charsetPropB);
			ax += (aw + (float)PROPB_GAP_WIDTH * cgs.screenXScale_Old);
		}
		s++;
	}

	trap_R_SetColor(NULL);
}

void UI_DrawBannerString(int x, int y, const char* str, int style, vec4_t color)
{
	const char*     s;
	int             ch;
	int             width;
	vec4_t          drawcolor;

	// find the width of the drawn text
	s = str;
	width = 0;
	while (*s)
	{
		ch = *s;
		if (ch == ' ')
		{
			width += PROPB_SPACE_WIDTH;
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			width += propMapB[ch - 'A'][2] + PROPB_GAP_WIDTH;
		}
		s++;
	}
	width -= PROPB_GAP_WIDTH;

	switch (style & UI_FORMATMASK)
	{
		case UI_CENTER:
			x -= width / 2;
			break;

		case UI_RIGHT:
			x -= width;
			break;

		case UI_LEFT:
		default:
			break;
	}

	if (style & UI_DROPSHADOW)
	{
		drawcolor[0] = drawcolor[1] = drawcolor[2] = 0;
		drawcolor[3] = color[3];
		UI_DrawBannerString2(x + 2, y + 2, str, drawcolor);
	}

	UI_DrawBannerString2(x, y, str, color);
}


int UI_ProportionalStringWidth(const char* str)
{
	const char*     s;
	int             ch;
	int             charWidth;
	int             width;

	s = str;
	width = 0;
	while (*s)
	{
		ch = *s & 127;
		charWidth = propMap[ch][2];
		if (charWidth != -1)
		{
			width += charWidth;
			width += PROP_GAP_WIDTH;
		}
		s++;
	}

	width -= PROP_GAP_WIDTH;
	return width;
}

static void UI_DrawProportionalString2(int x, int y, const char* str, vec4_t color, float sizeScale, qhandle_t charset)
{
	const char* s;
	unsigned char   ch; // bk001204 - unsigned
	float   ax;
	float   ay;
	float   aw;
	float   ah;
	float   frow;
	float   fcol;
	float   fwidth;
	float   fheight;

	// draw the colored text
	trap_R_SetColor(color);

	ax = x * cgs.screenXScale_Old + cgs.screenXBias_Old;
	ay = y * cgs.screenXScale_Old;

	s = str;
	while (*s)
	{
		ch = *s & 127;
		if (ch == ' ')
		{
			aw = (float)PROP_SPACE_WIDTH * cgs.screenXScale_Old * sizeScale;
		}
		else if (propMap[ch][2] != -1)
		{
			fcol = (float)propMap[ch][0] / 256.0f;
			frow = (float)propMap[ch][1] / 256.0f;
			fwidth = (float)propMap[ch][2] / 256.0f;
			fheight = (float)PROP_HEIGHT / 256.0f;
			aw = (float)propMap[ch][2] * cgs.screenXScale_Old * sizeScale;
			ah = (float)PROP_HEIGHT * cgs.screenXScale_Old * sizeScale;
			trap_R_DrawStretchPic(ax, ay, aw, ah, fcol, frow, fcol + fwidth, frow + fheight, charset);
		}
		else
		{
			aw = 0;
		}

		ax += (aw + (float)PROP_GAP_WIDTH * cgs.screenXScale_Old * sizeScale);
		s++;
	}

	trap_R_SetColor(NULL);
}

/*
=================
UI_ProportionalSizeScale
=================
*/
float UI_ProportionalSizeScale(int style)
{
	if (style & UI_SMALLFONT)
	{
		return 0.75;
	}

	return 1.00;
}


/*
=================
UI_DrawProportionalString
=================
*/
void UI_DrawProportionalString(int x, int y, const char* str, int style, vec4_t color)
{
	vec4_t  drawcolor;
	int     width;
	float   sizeScale;

	sizeScale = UI_ProportionalSizeScale(style);

	switch (style & UI_FORMATMASK)
	{
		case UI_CENTER:
			width = UI_ProportionalStringWidth(str) * sizeScale;
			x -= width / 2;
			break;

		case UI_RIGHT:
			width = UI_ProportionalStringWidth(str) * sizeScale;
			x -= width;
			break;

		case UI_LEFT:
		default:
			break;
	}

	if (style & UI_DROPSHADOW)
	{
		drawcolor[0] = drawcolor[1] = drawcolor[2] = 0;
		drawcolor[3] = color[3];
		UI_DrawProportionalString2(x + 2, y + 2, str, drawcolor, sizeScale, cgs.media.charsetProp);
	}

	if (style & UI_INVERSE)
	{
		drawcolor[0] = color[0] * 0.8;
		drawcolor[1] = color[1] * 0.8;
		drawcolor[2] = color[2] * 0.8;
		drawcolor[3] = color[3];
		UI_DrawProportionalString2(x, y, str, drawcolor, sizeScale, cgs.media.charsetProp);
		return;
	}

	if (style & UI_PULSE)
	{
		drawcolor[0] = color[0] * 0.8;
		drawcolor[1] = color[1] * 0.8;
		drawcolor[2] = color[2] * 0.8;
		drawcolor[3] = color[3];
		UI_DrawProportionalString2(x, y, str, color, sizeScale, cgs.media.charsetProp);

		drawcolor[0] = color[0];
		drawcolor[1] = color[1];
		drawcolor[2] = color[2];
		drawcolor[3] = 0.5 + 0.5 * sin(cg.time / (float)PULSE_DIVISOR);
		UI_DrawProportionalString2(x, y, str, drawcolor, sizeScale, cgs.media.charsetPropGlow);
		return;
	}

	UI_DrawProportionalString2(x, y, str, color, sizeScale, cgs.media.charsetProp);
}

#endif // Q3STATIC

static qboolean CG_OSPCharHexToInt(char c, int* out)
{
	if (c >= '0' && c <= '9')
	{
		*out = c - '0';
		return qtrue;
	}
	if (c >= 'a' && c <= 'f')
	{
		*out = c - 'a' + 10;
		return qtrue;
	}
	if (c >= 'A' && c <= 'F')
	{
		*out = c - 'A' + 10;
		return qtrue;
	}
	return qfalse;
}

qboolean CG_Hex16GetColor(const char* str, float* color)
{
	int d1;
	int d2;
	int color_int;
	if (!str) return qfalse;

	if (!CG_OSPCharHexToInt(str[0], &d1))
	{
		return  qfalse;
	}

	if (!CG_OSPCharHexToInt(str[1], &d2))
	{
		return  qfalse;
	}

	color_int = d1 * 16 + d2;

	*color = (float)color_int;
	*color /= 255.0f;

	return qtrue;
}

int CG_OSPDrawString(int x, int y, const char* str, int charWidth, int charHeight, vec4_t const colors, int maxChars, qboolean drawShadow)
{
	vec4_t lTextColor;
	float defaultBright;
	float char_w_f;
	float char_h_f;
	const char* str_ptr;
	int next_x;
	int printed;
	const static vec4_t textColor = { 1.0, 1.0, 1.0, 1.0};

	Vector4Copy(textColor, lTextColor);
	char_w_f = (float)charWidth * cgs.screenXScale_Old;
	char_h_f = (float)charHeight * cgs.screenYScale_Old;
	str_ptr = str;
	next_x = x;
	printed = 0;

	if (colors)
	{
		Vector4Copy(colors, lTextColor);
	}

	trap_R_SetColor(lTextColor);

	defaultBright = lTextColor[3];
	if (maxChars == 0)
	{
		maxChars = 32768;
	}

	while (str_ptr && *str_ptr != 0)
	{
		if (str_ptr[0] == '^' && str_ptr[1] != '^')
		{
			/*
			^B and ^b - make text blink
			^F        - makes the text display only at the first half of a second
			^f        - makes the text display only at the last half of a second
			^N        - resets control stuff like ^B, ^F, ^f
			^Xrrggbb  - allows the user to define the color using the rgb values (hex)
			            (e.g. ^XFF0000 is red, ^X777777 some kind of grey).
			*/
			char control_char;
			control_char = str_ptr[1];
			str_ptr += 2;

			switch (control_char)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if (!drawShadow)
					{
						unsigned int color_index;
						color_index = (control_char - 0x30) % 10;
						Vector3Copy(g_color_table[color_index], lTextColor);
						trap_R_SetColor(lTextColor);
					}
					break;
				case 'N':
				case 'n':
					lTextColor[3] = defaultBright;
					trap_R_SetColor(lTextColor);
					break;
				case 'B':
				{
					int b;
					b = cg.time & 0x7ff;
					if (b > 1024)
					{
						b = ~b & 0x7ff;
					}
					lTextColor[3] = b / 1463.0f + 0.3f;
					trap_R_SetColor(lTextColor);
				}
				break;
				case 'b':
				{
					int b;
					b = cg.time & 0x7ff;
					if (b > 1024)
					{
						b = ~b & 0x7ff;
					}
					lTextColor[3] = b / 1024.0f;
					trap_R_SetColor(lTextColor);
				}
				break;
				case 'f':
					if ((cg.time & 0x3ff) >= 512)
					{
						while (str_ptr && *str_ptr && !(str_ptr[0] == '^' && (str_ptr[1] == 'N' || str_ptr[1] == 'F')))
						{
							++str_ptr;
						}
					}
					break;
				case 'F':
					if ((cg.time & 0x3ff) < 512)
					{
						while (str_ptr && *str_ptr && !(str_ptr[0] == '^' && (str_ptr[1] == 'N' || str_ptr[1] == 'f')))
						{
							++str_ptr;
						}
					}
					break;
				case 'X':
				case 'x':
				{
					float r, g, b;
					if (!CG_Hex16GetColor(&str_ptr[0], &r))
					{
						break;
					}
					if (!CG_Hex16GetColor(&str_ptr[2], &g))
					{
						break;
					}
					if (!CG_Hex16GetColor(&str_ptr[4], &b))
					{
						break;
					}

					lTextColor[0] = r;
					lTextColor[1] = g;
					lTextColor[2] = b;
					if (drawShadow)
					{
						trap_R_SetColor(lTextColor);
					}
					str_ptr += 6;
				}
				break;
				default:
					break;
			}
		}
		else
		{
			if (++printed > maxChars)
			{
				return next_x - x;
			}
			if (*str_ptr != ' ')
			{
				float t1 = 0.0625f * (float)(*str_ptr >> 4);
				float s1 = 0.0625f * (float)(*str_ptr & 0x0f);
				qhandle_t shader;

				shader = ch_3waveFont.integer ? cgs.media.charsetShader1 : cgs.media.charsetShader;
				trap_R_DrawStretchPic(
				    (float)next_x * cgs.screenXScale_Old,
				    (float)y * cgs.screenYScale_Old,
				    char_w_f,
				    char_h_f,
				    s1,
				    t1,
				    s1 + 0.0625f,
				    t1 + 0.0625f,
				    shader);
			}
			next_x += charWidth;
			++str_ptr;
		}
	}
	trap_R_SetColor(colorWhite);
	return next_x - x;
}

int CG_OSPDrawStringWithShadow(int x, int y, const char* str, int charWidth, int charHeight, const vec4_t color, int maxChars)
{
	int shift_x;
	int shift_y;
	vec4_t shadow;
	const static vec4_t textShadowColor = { 0.0, 0.0, 0.0, 1.0};


	memcpy(shadow, textShadowColor, sizeof(shadow));

	if (color)
	{
		shadow[3] = color[3];
	}
	else
	{
		shadow[3] = 1.0;
	}

	shift_x = charWidth > 12 ? 2 : 1;
	shift_y = charHeight > 12 ? 2 : 1;


	CG_OSPDrawString(x + shift_x, y + shift_y, str, charWidth, charHeight, shadow, maxChars, qtrue);
	return CG_OSPDrawString(x, y, str, charWidth, charHeight, color, maxChars, qfalse);
}


