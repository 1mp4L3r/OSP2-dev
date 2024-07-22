#include "cg_local.h"
#include "cg_superhud_private.h"
#include "../qcommon/qcommon.h"

typedef enum
{
	SHUD_ELEMENT_SCORE_OWN,
	SHUD_ELEMENT_SCORE_NME,
	SHUD_ELEMENT_SCORE_MAX,
} shudElementScoreType_t;

typedef struct
{
	superhudConfig_t config;
	superhudTextContext_t position;
	shudElementScoreType_t type;
} shudElementScore;

static void* CG_SHUDElementScoreCreate(superhudConfig_t* config, shudElementScoreType_t type)
{
	shudElementScore* element;

	element = Z_Malloc(sizeof(*element));
	OSP_MEMORY_CHECK(element);

	memset(element, 0, sizeof(*element));

	memcpy(&element->config, config, sizeof(element->config));

	//load defaults
	if (!element->config.color.isSet)
	{
		element->config.color.isSet = qtrue;
		element->config.color.value.type = SUPERHUD_COLOR_RGBA;
		Vector4Set(element->config.color.value.rgba, 1, 0.7, 0, 1);
	}

	if (!element->config.text.isSet)
	{
		element->config.text.isSet = qtrue;
		Q_strncpyz(element->config.text.value, "%i", sizeof(element->config.text.value));
	}

	CG_SHUDTextMakeContext(&element->config, &element->position);

	element->type = type;

	return element;
}

void* CG_SHUDElementScoreOWNCreate(superhudConfig_t* config)
{
	return CG_SHUDElementScoreCreate(config, SHUD_ELEMENT_SCORE_OWN);
}

void* CG_SHUDElementScoreNMECreate(superhudConfig_t* config)
{
	return CG_SHUDElementScoreCreate(config, SHUD_ELEMENT_SCORE_NME);
}

void* CG_SHUDElementScoreMAXCreate(superhudConfig_t* config)
{
	return CG_SHUDElementScoreCreate(config, SHUD_ELEMENT_SCORE_MAX);
}

static qboolean CG_SHUDScoresGetMax(int* scores)
{
	*scores = cgs.fraglimit;
	return *scores > 0 && *scores > SCORE_NOT_PRESENT;
}

static qboolean CG_SHUDScoresGetOWN(int* scores)
{
	int clientNum = cg.snap->ps.clientNum;
	team_t team = CG_SHUDGetOurActiveTeam();

	switch (team)
	{
		case TEAM_FREE:
			*scores = cgs.clientinfo[cg.snap->ps.clientNum].score;
			return *scores != SCORE_NOT_PRESENT;
		case TEAM_RED:
		case TEAM_BLUE:
			*scores = cgs.scores1;
			return *scores != SCORE_NOT_PRESENT;
		case TEAM_SPECTATOR:
		case TEAM_4:
		case TEAM_5:
		case TEAM_6:
		case TEAM_7:
		case TEAM_NUM_TEAMS:
			break;
	}
	return qfalse;
}

static qboolean CG_SHUDScoresGetNME(int* scores)
{
	int clientNum = cg.snap->ps.clientNum;
	team_t team = CG_SHUDGetOurActiveTeam();

	switch (team)
	{
		case TEAM_FREE:
			*scores = cgs.scores1;
			if (*scores == cgs.clientinfo[cg.snap->ps.clientNum].score)
			{
				*scores = cgs.scores2;
			}
			return *scores != SCORE_NOT_PRESENT;
		case TEAM_RED:
		case TEAM_BLUE:
			*scores = cgs.scores2;
			return *scores != SCORE_NOT_PRESENT;
		case TEAM_SPECTATOR:
		case TEAM_4:
		case TEAM_5:
		case TEAM_6:
		case TEAM_7:
		case TEAM_NUM_TEAMS:
			break;
	}
	return qfalse;
}

void CG_SHUDElementScoreRoutine(void* context)
{
	shudElementScore* element = (shudElementScore*)context;
	const char* s;
	int scores;
	qboolean result = qfalse;

	switch (element->type)
	{
		case SHUD_ELEMENT_SCORE_OWN:
			result = CG_SHUDScoresGetOWN(&scores);
			break;
		case SHUD_ELEMENT_SCORE_NME:
			result = CG_SHUDScoresGetNME(&scores);
			break;
		case SHUD_ELEMENT_SCORE_MAX:
			result = CG_SHUDScoresGetMax(&scores);
			break;
	}
	if (!result) return;

	s = va(element->config.text.value, scores);

	CG_SHUDFill(&element->config);
	CG_SHUDTextPrint(s, &element->position);
}

void CG_SHUDElementScoreDestroy(void* context)
{
	if (context)
	{
		Z_Free(context);
	}
}

