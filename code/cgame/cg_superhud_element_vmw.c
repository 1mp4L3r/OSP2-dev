#include "cg_local.h"
#include "cg_superhud_private.h"
#include "../qcommon/qcommon.h"

typedef struct
{
	superhudConfig_t config;
	superhudTextContext_t ctx;
} shudElementVMW_t;

void* CG_SHUDElementVMWCreate(superhudConfig_t* config)
{
	shudElementVMW_t* element;

	element = Z_Malloc(sizeof(*element));
	OSP_MEMORY_CHECK(element);

	memset(element, 0, sizeof(*element));

	memcpy(&element->config, config, sizeof(element->config));

	CG_SHUDTextMakeContext(&element->config, &element->ctx);
	element->ctx.maxchars = MAX_QPATH;

	return element;
}

void CG_SHUDElementVMWRoutine(void* context)
{
	shudElementVMW_t* element = (shudElementVMW_t*)context;
	char* s;
	int time;

	if (cgs.voteTime == 0) return;

	if (cgs.voteModified)
	{
		cgs.voteModified = 0;
		trap_S_StartLocalSound(cgs.media.talkSound, CHAN_LOCAL_SOUND);
	}

	time = (30000 - (cg.time - cgs.voteTime)) / 1000;

	if (time < 0)
	{
		time = 0;
	}
	s = va("VOTE(%i):%s yes(F1):%i no(F2):%i", time, &cgs.voteString, cgs.voteYes, cgs.voteNo);

	CG_SHUDFill(&element->config);
	CG_SHUDTextPrint(s, &element->ctx);
}

void CG_SHUDElementVMWDestroy(void* context)
{
	if (context)
	{
		Z_Free(context);
	}
}

