#include "cg_superhud_private.h"
#include "cg_local.h"
#include "../qcommon/qcommon.h"


static superHUDConfigElement_t superHUDConfigItemElements[] =
{
	{ "!default", 0, },
	{ "predecorate", 1, CG_SHUDElementPreDCreate, CG_SHUDElementPreDRoutine, CG_SHUDElementPreDDestroy },
	{ "ammomessage", 2, CG_SHUDElementAmmoMessageCreate, CG_SHUDElementAmmoMessageRoutine, CG_SHUDElementAmmoMessageDestroy },
	{ "attackericon", 3, CG_SHUDElementAttackerIconCreate, CG_SHUDElementAttackerIconRoutine, CG_SHUDElementAttackerIconDestroy },
	{ "attackername", 4, CG_SHUDElementAttackerNameCreate, CG_SHUDElementAttackerNameRoutine, CG_SHUDElementAttackerNameDestroy },
	{ "chat1", 5, CG_SHUDElementChat1Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat2", 6, CG_SHUDElementChat2Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat3", 7, CG_SHUDElementChat3Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat4", 8, CG_SHUDElementChat4Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat5", 9, CG_SHUDElementChat5Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat6", 10, CG_SHUDElementChat6Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat7", 11, CG_SHUDElementChat7Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat8", 12, CG_SHUDElementChat8Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "console", 13, },
	{ "flagstatus_nme", 14, CG_SHUDElementFlagStatusNMECreate, CG_SHUDElementFlagStatusRoutine, CG_SHUDElementFlagStatusDestroy },
	{ "flagstatus_own", 15, CG_SHUDElementFlagStatusOWNCreate, CG_SHUDElementFlagStatusRoutine, CG_SHUDElementFlagStatusDestroy },
	{ "followmessage", 16, CG_SHUDElementFollowMessageCreate, CG_SHUDElementFollowMessageRoutine, CG_SHUDElementFollowMessageDestroy },
	{ "fps", 17, CG_SHUDElementFPSCreate, CG_SHUDElementFPSRoutine, CG_SHUDElementFPSDestroy, NULL, NULL},
	{ "fragmessage", 18, CG_SHUDElementFragMessageCreate, CG_SHUDElementFragMessageRoutine, CG_SHUDElementFragMessageDestroy, NULL, NULL},
	{ "gametime", 19, CG_SHUDElementGameTimeCreate, CG_SHUDElementGameTimeRoutine, CG_SHUDElementGameTimeDestroy },
	{ "gametype", 20, },
	{ "itempickup", 21, CG_SHUDElementItemPickupCreate, CG_SHUDElementItemPickupRoutine, CG_SHUDElementItemPickupDestroy },
	{ "itempickupicon", 22, CG_SHUDElementItemPickupIconCreate, CG_SHUDElementItemPickupIconRoutine, CG_SHUDElementItemPickupIconDestroy },
	{ "itemtimers1_icons", 23, },
	{ "itemtimers2_icons", 24, },
	{ "itemtimers3_icons", 25, },
	{ "itemtimers4_icons", 26, },
	{ "itemtimers1_times", 27, },
	{ "itemtimers2_times", 28, },
	{ "itemtimers3_times", 29, },
	{ "itemtimers4_times", 30, },
	{ "keydown_back", 31, },
	{ "keydown_crouch", 32, },
	{ "keydown_forward", 33, },
	{ "keydown_jump", 34, },
	{ "keydown_left", 35, },
	{ "keydown_right", 36, },
	{ "keyup_back", 37, },
	{ "keyup_crouch", 38, },
	{ "keyup_forward", 39, },
	{ "keyup_jump", 40, },
	{ "keyup_left", 41, },
	{ "keyup_right", 42, },
	{ "localtime", 43, CG_SHUDElementLocalTimeCreate, CG_SHUDElementLocalTimeRoutine, CG_SHUDElementLocalTimeDestroy },
	{ "multiview", 44, },
	{ "name_nme", 45, CG_SHUDElementNameNMECreate, CG_SHUDElementNameRoutine, CG_SHUDElementNameDestroy  },
	{ "name_own", 46, CG_SHUDElementNameOWNCreate, CG_SHUDElementNameRoutine, CG_SHUDElementNameDestroy  },
	{ "netgraph", 47, CG_SHUDElementNGCreate, CG_SHUDElementNGRoutine, CG_SHUDElementNGDestroy },
	{ "netgraphping", 48, CG_SHUDElementNGPCreate, CG_SHUDElementNGPRoutine, CG_SHUDElementNGPDestroy },
	{ "playerspeed", 49, CG_SHUDElementPlayerSpeedCreate, CG_SHUDElementPlayerSpeedRoutine, CG_SHUDElementPlayerSpeedDestroy },
	{ "powerup1_icon", 50, CG_SHUDElementPwIcon1Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup2_icon", 51, CG_SHUDElementPwIcon2Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup3_icon", 52, CG_SHUDElementPwIcon3Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup4_icon", 53, CG_SHUDElementPwIcon4Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup5_icon", 54, CG_SHUDElementPwIcon5Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup6_icon", 55, CG_SHUDElementPwIcon6Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup7_icon", 56, CG_SHUDElementPwIcon7Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup8_icon", 57, CG_SHUDElementPwIcon8Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup1_time", 58, CG_SHUDElementPwTime1Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup2_time", 59, CG_SHUDElementPwTime2Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup3_time", 60, CG_SHUDElementPwTime3Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup4_time", 61, CG_SHUDElementPwTime4Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup5_time", 62, CG_SHUDElementPwTime5Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup6_time", 63, CG_SHUDElementPwTime6Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup7_time", 64, CG_SHUDElementPwTime7Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup8_time", 65, CG_SHUDElementPwTime8Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "rankmessage", 66, CG_SHUDElementRankMessageCreate, CG_SHUDElementRankMessageRoutine, CG_SHUDElementRankMessageDestroy},
	{ "recordingdemo", 67, },
	{ "score_limit", 68, CG_SHUDElementScoreMAXCreate, CG_SHUDElementScoreRoutine, CG_SHUDElementScoreDestroy },
	{ "score_nme", 69, CG_SHUDElementScoreNMECreate, CG_SHUDElementScoreRoutine, CG_SHUDElementScoreDestroy },
	{ "score_own", 70, CG_SHUDElementScoreOWNCreate, CG_SHUDElementScoreRoutine, CG_SHUDElementScoreDestroy },
	{ "specmessage", 71, CG_SHUDElementSpecMessageCreate, CG_SHUDElementSpecMessageRoutine, CG_SHUDElementSpecMessageDestroy },
	{ "statusbar_armorbar", 72, CG_SHUDElementSBABCreate, CG_SHUDElementSBABRoutine, CG_SHUDElementSBABDestroy },
	{ "statusbar_armorcount", 73, CG_SHUDElementSBACCreate, CG_SHUDElementSBACRoutine, CG_SHUDElementSBACDestroy },
	{ "statusbar_armoricon", 74, CG_SHUDElementSBAICreate, CG_SHUDElementSBAIRoutine, CG_SHUDElementSBAIDestroy },
	{ "statusbar_ammobar", 75, CG_SHUDElementSBAmBCreate, CG_SHUDElementSBAmBRoutine, CG_SHUDElementSBAmBDestroy },
	{ "statusbar_ammocount", 76, CG_SHUDElementSBAmCCreate, CG_SHUDElementSBAmCRoutine, CG_SHUDElementSBAmCDestroy },
	{ "statusbar_ammoicon", 77, CG_SHUDElementSBAmICreate, CG_SHUDElementSBAmIRoutine, CG_SHUDElementSBAmIDestroy },
	{ "statusbar_healthbar", 78, CG_SHUDElementSBHBCreate, CG_SHUDElementSBHBRoutine, CG_SHUDElementSBHBDestroy },
	{ "statusbar_healthcount", 79, CG_SHUDElementSBHCCreate, CG_SHUDElementSBHCRoutine, CG_SHUDElementSBHCDestroy },
	{ "statusbar_healthicon", 80, CG_SHUDElementSBHICreate, CG_SHUDElementSBHIRoutine, CG_SHUDElementSBHIDestroy },
	{ "targetname", 81, CG_SHUDElementTargetNameCreate, CG_SHUDElementTargetNameRoutine, CG_SHUDElementTargetNameDestroy },
	{ "targetstatus", 82, },
	{ "teamcount_nme", 83, },
	{ "teamcount_own", 84, },
	{ "teamicon_nme", 85, },
	{ "teamicon_own", 86, },
	{ "team1", 87, },
	{ "team2", 88, },
	{ "team3", 89, },
	{ "team4", 90, },
	{ "team5", 91, },
	{ "team6", 92, },
	{ "team7", 93, },
	{ "team8", 94, },
	{ "votemessagearena", 95, },
	{ "votemessageworld", 96, CG_SHUDElementVMWCreate, CG_SHUDElementVMWRoutine, CG_SHUDElementVMWDestroy },
	{ "warmupinfo", 97, },
	{ "weaponlist", 98, },
	{ "weaponselection", 99, },
	{ "weaponselectionname", 100, },
	{ "chat", 101, },
	{ "gameevents", 102, },
	{ "team1_NME", 103, },
	{ "team2_NME", 104, },
	{ "team3_NME", 105, },
	{ "team4_NME", 106, },
	{ "team5_NME", 107, },
	{ "team6_NME", 108, },
	{ "team7_NME", 109, },
	{ "team8_NME", 110, },
	{ "rewardicons", 111, },
	{ "rewardnumbers", 112, },
	{ "postdecorate", 113, CG_SHUDElementPreDCreate, CG_SHUDElementPreDRoutine, CG_SHUDElementPreDDestroy },
	{ NULL, -1, NULL, NULL, NULL, NULL, NULL },
};

static superhudConfigParseStatus_t CG_SHUDConfigCommandParseColor(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseAlighH(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseAlighV(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseAngles(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseBgColor(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseDirection(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseDoublebar(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFade(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFadeDelay(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFill(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFont(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFontSize(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseImage(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseImageTC(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseItTeam(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseMargins(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseModel(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseMonospace(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseOffset(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseRect(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseText(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseTextAlign(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseTextOffset(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseTextStyle(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseTime(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseVisFlags(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseHlColor(configFileInfo_t* finfo, superhudConfig_t* config);
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseHlSize(configFileInfo_t* finfo, superhudConfig_t* config);

static superHUDConfigCommand_t superHUDConfigItemCommands[] =
{
	{ "alignh", CG_SHUDConfigCommandParseAlighH },
	{ "alignv", CG_SHUDConfigCommandParseAlighV },
	{ "angles", CG_SHUDConfigCommandParseAngles },
	{ "bgcolor", CG_SHUDConfigCommandParseBgColor },
	{ "hlcolor", CG_SHUDConfigCommandParseHlColor },
	{ "color", CG_SHUDConfigCommandParseColor },
	{ "direction", CG_SHUDConfigCommandParseDirection },
	{ "doublebar", CG_SHUDConfigCommandParseDoublebar },
	{ "fade", CG_SHUDConfigCommandParseFade },
	{ "fadedelay", CG_SHUDConfigCommandParseFadeDelay },
	{ "fill", CG_SHUDConfigCommandParseFill },
	{ "font", CG_SHUDConfigCommandParseFont },
	{ "fontsize", CG_SHUDConfigCommandParseFontSize },
	{ "image", CG_SHUDConfigCommandParseImage },
	{ "imagetc", CG_SHUDConfigCommandParseImageTC },
	{ "itteam", CG_SHUDConfigCommandParseItTeam },
	{ "margins", CG_SHUDConfigCommandParseMargins },
	{ "model", CG_SHUDConfigCommandParseModel },
	{ "monospace", CG_SHUDConfigCommandParseMonospace },
	{ "offset", CG_SHUDConfigCommandParseOffset },
	{ "rect", CG_SHUDConfigCommandParseRect },
	{ "text", CG_SHUDConfigCommandParseText },
	{ "textalign", CG_SHUDConfigCommandParseTextAlign },
	{ "textoffset", CG_SHUDConfigCommandParseTextOffset },
	{ "textstyle", CG_SHUDConfigCommandParseTextStyle },
	{ "time", CG_SHUDConfigCommandParseTime },
	{ "visflags", CG_SHUDConfigCommandParseVisFlags},
	{ "hlsize", CG_SHUDConfigCommandParseHlSize },
	{ NULL, NULL, NULL },
};

#define CG_SHUD_CONFIG_INFO_IS_TEXT_CHARACTER(CCC) \
       ((CCC >= 'a' && CCC <= 'z') \
      || (CCC >= 'A' && CCC <= 'Z') \
      || (CCC >= '0' && CCC <= '9') \
      || (CCC == '_') \
      || (CCC == '!') \
       )

#define CG_SHUD_CONFIG_INFO_IS_TEXT_SPLITTER(CCC) \
       ( (CCC == '{') \
      || (CCC == '}') \
      || (CCC == ',') \
       )

#define CG_SHUD_CONFIG_INFO_IS_CHAR_END_OF_LINE(CCC) \
       ( (CCC == '#') \
      || (CCC == '\n') \
      || (CCC == 0) \
       )

#define CG_SHUD_CONFIG_INFO_GET_CHAR(CFI) CFI->last_line->line[CFI->pos]
#define CG_SHUD_CONFIG_INFO_NEXT_CHAR(CFI) ++CFI->pos
#define CG_SHUD_CONFIG_INFO_NEXT_LINE(CFI) CFI->last_line = CFI->last_line->next; CFI->pos = 0
#define CG_SHUD_CONFIG_INFO_IS_END_OF_FILE(CFI) (!CFI->last_line)

#define SHUD_CONFIG_ITEMS_DICT_SIZE   256

static superHUDConfigElement_t* superHUDConfigItemElementsDict[SHUD_CONFIG_ITEMS_DICT_SIZE];
static superHUDConfigCommand_t* superHUDConfigItemCommandsDict[SHUD_CONFIG_ITEMS_DICT_SIZE];

const superHUDConfigElement_t* CG_SHUDFindConfigElementItem(const char* name)
{
	const superHUDConfigElement_t* target = superHUDConfigItemElementsDict[Com_GenerateHashValue(name, SHUD_CONFIG_ITEMS_DICT_SIZE)];

	while (target && Q_stricmp(name, target->name))
	{
		target = target->next;
	}
	return target;
}

const superHUDConfigCommand_t* CG_SHUDFindConfigCommandItem(const char* name)
{
	const superHUDConfigCommand_t* target = superHUDConfigItemCommandsDict[Com_GenerateHashValue(name, SHUD_CONFIG_ITEMS_DICT_SIZE)];

	while (target && Q_stricmp(name, target->name))
	{
		target = target->next;
	}
	return target;
}

/*
 * Skip spaces, comments, new lines, comma
 */
static superhudConfigParseStatus_t CG_SHUDConfigSkipSCN(configFileInfo_t* finfo)
{
	qboolean skip;
	qboolean skip_line;
	char c;

	do
	{
		c = CG_SHUD_CONFIG_INFO_GET_CHAR(finfo);

		skip = c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == ',';
		skip_line = c == '#' || c == 0;

		if (skip_line)
		{
			CG_SHUD_CONFIG_INFO_NEXT_LINE(finfo);
			if (CG_SHUD_CONFIG_INFO_IS_END_OF_FILE(finfo))
			{
				return SUPERHUD_CONFIG_END_OF_FILE;
			}
		}
		else if (skip)
		{
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
		}
	}
	while (skip || skip_line);

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDParseString(configFileInfo_t* finfo, char* value, int len)
{
	superhudConfigParseStatus_t status;
	int rc;
	qboolean skip;
	char c;
	char* src;
	char* dst;
	int lenMax = 0;

	status = CG_SHUDConfigSkipSCN(finfo);
	if (status != SUPERHUD_CONFIG_OK) return status;

	dst = finfo->last_line->line + finfo->pos;

	do
	{
		c = *dst;
		if (c == 0 || c == '#' || c == '\n' || c == ';' || c == '}')
		{
			break;
		}
		++lenMax;
		++dst;
	}
	while (qtrue);

	if (!lenMax)
	{
		return SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;
	}

	dst = Z_Malloc(lenMax + 1);
	OSP_MEMORY_CHECK(dst);

	src = Z_Malloc(lenMax + 1);
	OSP_MEMORY_CHECK(src);

	memcpy(src, finfo->last_line->line + finfo->pos, lenMax);
	src[lenMax] = 0;

	rc = Q_sscanf(src, "\"%s\"", dst);

	if (rc <= 0)
	{
		rc = Q_sscanf(src, "%s", dst);
	}

	if (rc <= 0)
	{
		Z_Free(dst);
		Z_Free(src);
		return SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;
	}

	finfo->pos += lenMax;

	Q_strncpyz(value, dst, len);

	Z_Free(dst);
	Z_Free(src);

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDParseFloat(configFileInfo_t* finfo, float* value)
{
	superhudConfigParseStatus_t status;
	int rc;
	qboolean skip;
	char c;

	status = CG_SHUDConfigSkipSCN(finfo);
	if (status != SUPERHUD_CONFIG_OK) return status;

	rc = Q_sscanf(finfo->last_line->line + finfo->pos, "%f", value);

	if (rc != 1) return SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;

	do
	{
		c = CG_SHUD_CONFIG_INFO_GET_CHAR(finfo);

		skip = (c >= '0' && c <= '9') || c == '.' || c == '-';

		if (skip)
		{
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
		}
	}
	while (skip);

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDParseInt(configFileInfo_t* finfo, int* value)
{
	superhudConfigParseStatus_t status;
	int rc;
	qboolean skip;
	char c;

	status = CG_SHUDConfigSkipSCN(finfo);
	if (status != SUPERHUD_CONFIG_OK) return status;

	rc = Q_sscanf(finfo->last_line->line + finfo->pos, "%i", value);

	if (rc != 1) return SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;

	do
	{
		c = CG_SHUD_CONFIG_INFO_GET_CHAR(finfo);

		skip = (c >= '0' && c <= '9') || c == '-';

		if (skip)
		{
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
		}
	}
	while (skip);

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDParseVec4t(configFileInfo_t* finfo, vec4_t color)
{
	superhudConfigParseStatus_t status;

	status = CG_SHUDParseFloat(finfo, &color[0]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	status = CG_SHUDParseFloat(finfo, &color[1]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	status = CG_SHUDParseFloat(finfo, &color[2]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	status = CG_SHUDParseFloat(finfo, &color[3]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDParseVec3t(configFileInfo_t* finfo, vec3_t color)
{
	superhudConfigParseStatus_t status;

	status = CG_SHUDParseFloat(finfo, &color[0]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	status = CG_SHUDParseFloat(finfo, &color[1]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	status = CG_SHUDParseFloat(finfo, &color[2]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDParseVec2t(configFileInfo_t* finfo, vec2_t color)
{
	superhudConfigParseStatus_t status;

	status = CG_SHUDParseFloat(finfo, &color[0]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	status = CG_SHUDParseFloat(finfo, &color[1]);
	if (status != SUPERHUD_CONFIG_OK) return status;

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDConfigCommandParseTextStyle(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->textStyle.isSet = qfalse;
	status = CG_SHUDParseInt(finfo, &config->textStyle.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->textStyle.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDConfigCommandParseTime(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->time.isSet = qfalse;
	status = CG_SHUDParseInt(finfo, &config->time.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->time.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

static superhudConfigParseStatus_t CG_SHUDConfigCommandParseVisFlags(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->visflags.isSet = qfalse;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse HLCOLOR r g b a
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseHlColor(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;

	config->hlcolor.isSet = qfalse;

	status = CG_SHUDParseVec4t(finfo, config->hlcolor.value);
	if (status != SUPERHUD_CONFIG_OK) return status;

	config->hlcolor.isSet = qtrue;

	return status;
}

/*
 * parse HLSIZE x y
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseHlSize(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->hlsize.isSet = qfalse;
	status = CG_SHUDParseInt(finfo, &config->hlsize.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->hlsize.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse TEXTOFFSET x y
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseTextOffset(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->textOffset.isSet = qfalse;
	status = CG_SHUDParseVec2t(finfo, config->textOffset.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->textOffset.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse TEXTALIGN L / C / R
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseTextAlign(configFileInfo_t* finfo, superhudConfig_t* config)
{
	char c;
	int rc;
	superhudConfigParseStatus_t status;

	config->textAlign.isSet = qfalse;

	/* skip to value */
	status = CG_SHUDConfigSkipSCN(finfo);

	if (status != SUPERHUD_CONFIG_OK) return status;

	c = tolower(CG_SHUD_CONFIG_INFO_GET_CHAR(finfo));
	switch (c)
	{
		case 'l':
			config->textAlign.value = SUPERHUD_ALIGNH_LEFT;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'c':
			config->textAlign.value = SUPERHUD_ALIGNH_CENTER;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'r':
			config->textAlign.value = SUPERHUD_ALIGNH_RIGHT;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		default:
			status = SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;
			break;
	}

	if (status == SUPERHUD_CONFIG_OK) config->textAlign.isSet = qtrue;
	return status;
}

/*
 * parse TEXT str
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseText(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->text.isSet = qfalse;
	status = CG_SHUDParseString(finfo, config->text.value, MAX_QPATH);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->text.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse RECT x y w h
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseRect(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->rect.isSet = qfalse;
	status = CG_SHUDParseVec4t(finfo, config->rect.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->rect.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse OFFSET x y z
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseOffset(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->offset.isSet = qfalse;
	status = CG_SHUDParseVec3t(finfo, config->offset.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->offset.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse MONOSPACE
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseMonospace(configFileInfo_t* finfo, superhudConfig_t* config)
{
	config->monospace.isSet = qtrue;
	(void) config;
	(void) finfo;
	return SUPERHUD_CONFIG_OK;
}

/*
 * parse MODEL str
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseModel(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->model.isSet = qfalse;
	status = CG_SHUDParseString(finfo, config->model.value, MAX_QPATH);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->model.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse MARGINS l t r b
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseMargins(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->margins.isSet = qfalse;
	status = CG_SHUDParseVec4t(finfo, config->margins.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->margins.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse ITTEAM B/R/N/O/E
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseItTeam(configFileInfo_t* finfo, superhudConfig_t* config)
{
	char c;
	int rc;
	superhudConfigParseStatus_t status;

	config->itTeam.isSet = qfalse;

	/* skip to value */
	status = CG_SHUDConfigSkipSCN(finfo);

	if (status != SUPERHUD_CONFIG_OK) return status;

	c = tolower(CG_SHUD_CONFIG_INFO_GET_CHAR(finfo));
	switch (c)
	{
		case 'b':
			config->itTeam.value = SUPERHUD_ITTEAM_BLUE;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'r':
			config->itTeam.value = SUPERHUD_ITTEAM_RED;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'n':
			config->itTeam.value = SUPERHUD_ITTEAM_NEUTRAL;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'o':
			config->itTeam.value = SUPERHUD_ITTEAM_OWN;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'e':
			config->itTeam.value = SUPERHUD_ITTEAM_ENEMY;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		default:
			status = SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;
			break;
	}

	if (status == SUPERHUD_CONFIG_OK) config->itTeam.isSet = qtrue;
	return status;
}

/*
 * parse IMAGETC l t r b
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseImageTC(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->imagetc.isSet = qfalse;
	status = CG_SHUDParseVec4t(finfo, config->imagetc.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->imagetc.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse IMAGE str
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseImage(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->image.isSet = qfalse;
	status = CG_SHUDParseString(finfo, config->image.value, MAX_QPATH);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->image.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse FONTSIZE xsize [ysize]
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFontSize(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->fontsize.isSet = qfalse;

	status = CG_SHUDParseFloat(finfo, &config->fontsize.value[0]);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}

	status = CG_SHUDParseFloat(finfo, &config->fontsize.value[1]);
	if (status != SUPERHUD_CONFIG_OK)
	{
		config->fontsize.value[1] = config->fontsize.value[0];
	}

	config->fontsize.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse FONT str
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFont(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->font.isSet = qfalse;
	status = CG_SHUDParseString(finfo, config->font.value, MAX_QPATH);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->font.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse FILL
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFill(configFileInfo_t* finfo, superhudConfig_t* config)
{
	config->fill.isSet = qtrue;
	(void) config;
	(void) finfo;
	return SUPERHUD_CONFIG_OK;
}

/*
 * parse FADEDELAY t
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFadeDelay(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	float fadeDelay;

	config->fadedelay.isSet = qfalse;
	status = CG_SHUDParseFloat(finfo, &fadeDelay);
	if (status != SUPERHUD_CONFIG_OK)
	{
		return status;
	}
	config->fadedelay.isSet = qtrue;
	config->fadedelay.value = (int)(fadeDelay);

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse FADE [r g b a]
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseFade(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	config->fade.isSet = qtrue;
	status = CG_SHUDParseVec4t(finfo, config->fade.value);
	if (status != SUPERHUD_CONFIG_OK)
	{
		// it is ok if there are no colors
		Vector4Clear(config->fade.value);
	}

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse DOUBLEBAR
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseDoublebar(configFileInfo_t* finfo, superhudConfig_t* config)
{
	config->doublebar.isSet = qtrue;
	(void) config;
	(void) finfo;
	return SUPERHUD_CONFIG_OK;
}

/*
 * parse BGCOLOR r g b a
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseBgColor(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;

	config->bgcolor.isSet = qfalse;

	status = CG_SHUDParseVec4t(finfo, config->bgcolor.value);
	if (status != SUPERHUD_CONFIG_OK) return status;

	config->bgcolor.isSet = qtrue;

	return status;
}

/*
 * parse ANGLES p y r [e]
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseAngles(configFileInfo_t* finfo, superhudConfig_t* config)
{
	superhudConfigParseStatus_t status;
	float e = .0f;

	config->angles.isSet = qfalse;
	//p y r
	status = CG_SHUDParseVec3t(finfo, config->angles.value);
	if (status != SUPERHUD_CONFIG_OK) return status;


	//[e]
	do
	{
		status = CG_SHUDConfigSkipSCN(finfo);
		if (status != SUPERHUD_CONFIG_OK)  break;

		status = CG_SHUDParseFloat(finfo, &e);
		if (status != SUPERHUD_CONFIG_OK) break;
	}
	while (qfalse);

	config->angles.value[3] = e;
	config->angles.isSet = qtrue;

	return SUPERHUD_CONFIG_OK;
}

/*
 * parse horizontal align command: L/C/R
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseAlighH(configFileInfo_t* finfo, superhudConfig_t* config)
{
	char c;
	int rc;
	superhudConfigParseStatus_t status;

	config->alignH.isSet = qfalse;

	/* skip to value */
	status = CG_SHUDConfigSkipSCN(finfo);

	if (status != SUPERHUD_CONFIG_OK) return status;

	c = tolower(CG_SHUD_CONFIG_INFO_GET_CHAR(finfo));
	switch (c)
	{
		case 'l':
			config->alignH.value = SUPERHUD_ALIGNH_LEFT;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'c':
			config->alignH.value = SUPERHUD_ALIGNH_CENTER;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'r':
			config->alignH.value = SUPERHUD_ALIGNH_RIGHT;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		default:
			status = SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;
			break;
	}

	if (status == SUPERHUD_CONFIG_OK) config->alignH.isSet = qtrue;
	return status;
}

/*
2024-07-11T04:46:02Z MORION_SWITCH daemon.warn phyd[895]: Port 8: Media changed to 10/100/1000BASE-T
 * parse vertical align command: T/C/B
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseAlighV(configFileInfo_t* finfo, superhudConfig_t* config)
{
	char c;
	int rc;
	superhudConfigParseStatus_t status;

	config->alignV.isSet = qfalse;

	/* skip to value */
	status = CG_SHUDConfigSkipSCN(finfo);

	if (status != SUPERHUD_CONFIG_OK) return status;

	c = tolower(CG_SHUD_CONFIG_INFO_GET_CHAR(finfo));
	switch (c)
	{
		case 't':
			config->alignV.value = SUPERHUD_ALIGNV_TOP;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'c':
			config->alignV.value = SUPERHUD_ALIGNV_CENTER;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'b':
			config->alignV.value = SUPERHUD_ALIGNV_BOTTOM;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		default:
			status = SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;
			break;
	}

	if (status == SUPERHUD_CONFIG_OK) config->alignV.isSet = qtrue;
	return status;
}

/*
 * parse direction L | R | T | B
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseDirection(configFileInfo_t* finfo, superhudConfig_t* config)
{
	char c;
	superhudConfigParseStatus_t status;

	config->direction.isSet = qfalse;

	/* skip to value */
	status = CG_SHUDConfigSkipSCN(finfo);

	if (status != SUPERHUD_CONFIG_OK) return status;

	c = tolower(CG_SHUD_CONFIG_INFO_GET_CHAR(finfo));
	switch (c)
	{
		case 'l':
			config->direction.value = SUPERHUD_DIR_LEFT_TO_RIGHT;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'r':
			config->direction.value = SUPERHUD_DIR_RIGHT_TO_LEFT;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 't':
			config->direction.value = SUPERHUD_DIR_TOP_TO_BOTTOM;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'b':
			config->direction.value = SUPERHUD_DIR_BOTTOM_TO_TOP;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		default:
			status = SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;
			break;
	}

	if (status == SUPERHUD_CONFIG_OK) config->direction.isSet = qtrue;
	return status;

}

/*
 * parse color command: rgba/t/e/I
 */
static superhudConfigParseStatus_t CG_SHUDConfigCommandParseColor(configFileInfo_t* finfo, superhudConfig_t* config)
{
	char c;
	superhudConfigParseStatus_t status;

	config->color.isSet = qfalse;

	/* skip to value */
	status = CG_SHUDConfigSkipSCN(finfo);

	if (status != SUPERHUD_CONFIG_OK) return status;

	c = tolower(CG_SHUD_CONFIG_INFO_GET_CHAR(finfo));
	switch (c)
	{
		case 't':
			config->color.value.type = SUPERHUD_COLOR_T;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'e':
			config->color.value.type = SUPERHUD_COLOR_E;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		case 'i':
			config->color.value.type = SUPERHUD_COLOR_I;
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(finfo);
			break;
		default:
			config->color.value.type = SUPERHUD_COLOR_RGBA;
			status = CG_SHUDParseVec4t(finfo, config->color.value.rgba);
			break;
	}

	if (status == SUPERHUD_CONFIG_OK) config->color.isSet = qtrue;
	return status;
}

/*
 * Split NULL-terminated config file to lines
 */
qboolean CG_SHUDFileInfoInit(configFileInfo_t* info, const char* fileContent)
{
	int line_number = 0;
	const char* tmp;
	const char* startline = fileContent;
	const char* endline;
	const char* endoffile = fileContent + strlen(fileContent) + 1;

	memset(info, 0, sizeof(*info));

	while (startline < endoffile && *startline != 0)
	{
		endline = strchr(startline, '\n');
		if (endline == NULL)
		{
			endline = endoffile - 1;
		}

		if (!info->root)
		{
			info->root = Z_Malloc(sizeof(*info->root));
			OSP_MEMORY_CHECK(info->root);
			info->last_line = info->root;
		}
		else
		{
			info->last_line->next = Z_Malloc(sizeof(*info->root));
			OSP_MEMORY_CHECK(info->last_line->next);
			info->last_line = info->last_line->next;
		}

		info->last_line->line_number = ++line_number;
		info->last_line->size = endline - startline;
		info->last_line->line = Z_Malloc(info->last_line->size + 1);
		OSP_MEMORY_CHECK(info->last_line->line);
		memcpy(info->last_line->line, startline, info->last_line->size);
		info->last_line->line[info->last_line->size] = 0;
		if (info->last_line->line[info->last_line->size - 1] == 0x0d)
		{
			//skip /r
			info->last_line->line[info->last_line->size - 1] = 0;
		}

		startline = endline + 1;
	}
	info->last_line = info->root;

	return line_number > 0;
}

void CG_SHUDFileInfoTeardown(configFileInfo_t* cfi)
{
	configFileLine_t* to_delete;

	while (cfi->root)
	{
		to_delete = cfi->root;
		cfi->root = to_delete->next;

		if (to_delete->line)
		{
			Z_Free(to_delete->line);
		}
		Z_Free(to_delete);
	}
	cfi->last_line = NULL;
}

/* Поиск элемента
 *
 * пропускаем пробелы
 * пропускаем комментарии
 * пропускаем новую строку
 * берем токен
 * пропускаем пробелы
 * пропускаем комментарии
 * пропускаем новую строку
 * находим {
 *
 * ошибки:
 *
 * SUPERHUD_CONFIG_WRONG_ELEMENT_NAME
 * SUPERHUD_CONFIG_LOST_ELEMENT_BODY
 * SUPERHUD_CONFIG_END_OF_FILE
 *
 *
 */

const superhudConfigParseElement_t CG_SHUDFileInfoGetElementItem(configFileInfo_t* cfi)
{
	char elementName[MAX_QPATH];
	int i;
	char c;
	qboolean skip;
	qboolean skip_line;
	qboolean start_of_body;

	superhudConfigParseElement_t result = {NULL, SUPERHUD_CONFIG_OK};
	// find start of element name
	do
	{
		c = CG_SHUD_CONFIG_INFO_GET_CHAR(cfi);

		skip = c == ' ' || c < 32;
		skip_line = c == '#' || c == 0;

		if (skip_line)
		{
			CG_SHUD_CONFIG_INFO_NEXT_LINE(cfi);
			if (CG_SHUD_CONFIG_INFO_IS_END_OF_FILE(cfi))
			{
				CG_SHUD_CONFIG_INFO_NEXT_CHAR(cfi);
				result.status = SUPERHUD_CONFIG_END_OF_FILE;
				return result;
			}
		}
		else if (skip)
		{
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(cfi);
		}
	}
	while (skip || skip_line);

	// copy text to local buffer
	i = 0;
	while (CG_SHUD_CONFIG_INFO_IS_TEXT_CHARACTER(c))
	{
		if (i < (MAX_QPATH - 1))
		{
			elementName[i++] = c;
		}
		CG_SHUD_CONFIG_INFO_NEXT_CHAR(cfi);
		c = CG_SHUD_CONFIG_INFO_GET_CHAR(cfi);
	}
	elementName[i] = 0;
	result.item = CG_SHUDFindConfigElementItem(elementName);
	if (result.item)
	{
		result.status = SUPERHUD_CONFIG_OK;
	}
	else
	{
		result.status = SUPERHUD_CONFIG_WRONG_ELEMENT_NAME;
		return result;
	}

	// find start of element body
	do
	{
		c = CG_SHUD_CONFIG_INFO_GET_CHAR(cfi);

		start_of_body = c == '{';
		skip = c == ' ' || c < 32;
		skip_line = c == '#' || c == 0;

		if (skip_line)
		{
			CG_SHUD_CONFIG_INFO_NEXT_LINE(cfi);
			if (CG_SHUD_CONFIG_INFO_IS_END_OF_FILE(cfi))
			{
				result.status = SUPERHUD_CONFIG_END_OF_FILE;
				return result;
			}
		}
		else if (skip)
		{
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(cfi);
		}
		else if (start_of_body)
		{
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(cfi);
			break;
		}
		else
		{
			result.status = SUPERHUD_CONFIG_UNEXPECTED_CHARACTER;
			return result;
		}
	}
	while (skip || skip_line);

	return result;
}

/* Поиск команды
 *
 * пропускаем пробелы
 * пропускаем комментарии
 * пропускаем новую строку
 * берем токен
 *
 * SUPERHUD_CONFIG_WRONG_COMMAND_NAME
 * SUPERHUD_CONFIG_LOST_ELEMENT_BODY
 * SUPERHUD_CONFIG_END_OF_FILE
 *
 *
 */

const superhudConfigParseCommand_t CG_SHUDFileInfoGetCommandItem(configFileInfo_t* cfi)
{
	char commandName[MAX_QPATH];
	int i;
	char c;
	qboolean skip;
	qboolean skip_line;
	qboolean end_of_element;
	superhudConfigParseCommand_t result = {NULL, SUPERHUD_CONFIG_OK};

	// find start of element name
	do
	{
		c = CG_SHUD_CONFIG_INFO_GET_CHAR(cfi);

		skip = c == ' ' || c < 32 || c == ';';
		skip_line = c == '#' || c == 0;
		end_of_element = c == '}';

		if (skip_line)
		{
			CG_SHUD_CONFIG_INFO_NEXT_LINE(cfi);
			if (CG_SHUD_CONFIG_INFO_IS_END_OF_FILE(cfi))
			{
				result.status = SUPERHUD_CONFIG_END_OF_FILE;
				return result;
			}
		}
		else if (skip)
		{
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(cfi);
		}
		else if (end_of_element)
		{
			CG_SHUD_CONFIG_INFO_NEXT_CHAR(cfi);
			result.status = SUPERHUD_CONFIG_END_OF_ELEMENT;
			return result;
		}
	}
	while (skip || skip_line);

	// copy text to local buffer
	i = 0;
	while (CG_SHUD_CONFIG_INFO_IS_TEXT_CHARACTER(c))
	{
		if (i < (MAX_QPATH - 1))
		{
			commandName[i++] = c;
		}
		CG_SHUD_CONFIG_INFO_NEXT_CHAR(cfi);
		c = CG_SHUD_CONFIG_INFO_GET_CHAR(cfi);
	}
	commandName[i] = 0;

	result.item = CG_SHUDFindConfigCommandItem(commandName);
	if (result.item)
	{
		result.status = SUPERHUD_CONFIG_OK;
	}
	else
	{
		result.status = SUPERHUD_CONFIG_WRONG_COMMAND_NAME;
	}

	return result;
}

/*
 * Инициализация парсера
 */
void CG_SHUDParserInit(void)
{
	int i = 0;
	static qboolean initialized = qfalse;

	if (initialized)
	{
		return;
	}

	while (superHUDConfigItemElements[i].name)
	{
		superHUDConfigElement_t** target = NULL;
		superHUDConfigElement_t* collision = NULL;

		unsigned long hash = Com_GenerateHashValue(superHUDConfigItemElements[i].name, SHUD_CONFIG_ITEMS_DICT_SIZE);

		/* store in the hash table */
		target = &superHUDConfigItemElementsDict[hash];
		if (*target == NULL)
		{
			*target = &superHUDConfigItemElements[i];
		}
		else
		{
			collision = *target;
			//collision
			while (collision->next)
			{
				collision = collision->next;
			}
			collision->next = &superHUDConfigItemElements[i];
		}
		++i;
	}

	i = 0;
	while (superHUDConfigItemCommands[i].name)
	{
		superHUDConfigCommand_t** target = NULL;
		superHUDConfigCommand_t* collision = NULL;

		unsigned long hash = Com_GenerateHashValue(superHUDConfigItemCommands[i].name, SHUD_CONFIG_ITEMS_DICT_SIZE);

		/* store in the hash table */
		target = &superHUDConfigItemCommandsDict[hash];
		if (*target == NULL)
		{
			*target = &superHUDConfigItemCommands[i];
		}
		else
		{
			collision = *target;
			//collision
			while (collision->next)
			{
				collision = collision->next;
			}
			collision->next = &superHUDConfigItemCommands[i];
		}
		++i;
	}

	initialized = qtrue;
}

