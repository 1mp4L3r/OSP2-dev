#include "cg_local.h"
#include "cg_superhud_private.h"
#include "../qcommon/qcommon.h"

#define FPS_MAX_FRAMES  32
typedef struct
{
	superhudConfig_t config;
	float timeAverage;
	int framesNum;
	int timePrev;
	superhudTextContext_t ctx;
} shudElementFPS_t;

void* CG_SHUDElementFPSCreate(superhudConfig_t* config)
{
	shudElementFPS_t* fps;

	fps = Z_Malloc(sizeof(*fps));
	OSP_MEMORY_CHECK(fps);

	memset(fps, 0, sizeof(*fps));

	memcpy(&fps->config, config, sizeof(fps->config));

	CG_SHUDTextMakeContext(&fps->config, &fps->ctx);
	fps->ctx.maxchars = 6;

	return fps;
}

void CG_SHUDElementFPSRoutine(void* context)
{
	shudElementFPS_t* element = (shudElementFPS_t*)context;
	char*   s;
	int     fps_val;
	int     t;

	// don't use serverTime, because that will be drifting to
	// correct for internet lag changes, timescales, timedemos, etc
	t = trap_Milliseconds();
	if (element->timePrev == 0)
	{
		// skip first measure result
		element->timePrev = t;
		return;
	}
	element->timeAverage *= element->framesNum;
	element->timeAverage += t - element->timePrev;
	element->timeAverage /= ++element->framesNum;
	element->timePrev = t;

	if (element->framesNum > FPS_MAX_FRAMES)
	{
		element->framesNum = FPS_MAX_FRAMES;
	}

	fps_val = 1000.0f / element->timeAverage;

	s = va("%ifps", fps_val);

	CG_SHUDFill(&element->config);

	CG_SHUDTextPrint(s, &element->ctx);
}

void CG_SHUDElementFPSDestroy(void* context)
{
	if (context)
	{
		Z_Free(context);
	}
}
