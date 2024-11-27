#include "cg_superhud_private.h"

static superhudGlobalContext_t superhudGlobalContext;

static superHUDConfigElement_t superHUDConfigItemElements[] =
{
	{ "!default", 0, },
	{ "predecorate", 0, CG_SHUDElementDecorCreate, CG_SHUDElementDecorRoutine, CG_SHUDElementDecorDestroy },
	{ "ammomessage", 0, CG_SHUDElementAmmoMessageCreate, CG_SHUDElementAmmoMessageRoutine, CG_SHUDElementAmmoMessageDestroy },
	{ "attackericon", 0, CG_SHUDElementAttackerIconCreate, CG_SHUDElementAttackerIconRoutine, CG_SHUDElementAttackerIconDestroy },
	{ "attackername", 0, CG_SHUDElementAttackerNameCreate, CG_SHUDElementAttackerNameRoutine, CG_SHUDElementAttackerNameDestroy },
	{ "chat1", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat1Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat2", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat2Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat3", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat3Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat4", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat4Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat5", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat5Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat6", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat6Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat7", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat7Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat8", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat8Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat9", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat9Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat10", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat10Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat11", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat11Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat12", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat12Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat13", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat13Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat14", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat14Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat15", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat15Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "chat16", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementChat16Create, CG_SHUDElementChatRoutine, CG_SHUDElementChatDestroy },
	{ "console", 0, },
	{ "flagstatus_nme", SE_TEAM_ONLY, CG_SHUDElementFlagStatusNMECreate, CG_SHUDElementFlagStatusRoutine, CG_SHUDElementFlagStatusDestroy },
	{ "flagstatus_own", SE_TEAM_ONLY, CG_SHUDElementFlagStatusOWNCreate, CG_SHUDElementFlagStatusRoutine, CG_SHUDElementFlagStatusDestroy },
	{ "followmessage", 0, CG_SHUDElementFollowMessageCreate, CG_SHUDElementFollowMessageRoutine, CG_SHUDElementFollowMessageDestroy },
	{ "fps", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementFPSCreate, CG_SHUDElementFPSRoutine, CG_SHUDElementFPSDestroy },
	{ "fragmessage", 0, CG_SHUDElementFragMessageCreate, CG_SHUDElementFragMessageRoutine, CG_SHUDElementFragMessageDestroy },
	{ "gametime", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementGameTimeCreate, CG_SHUDElementGameTimeRoutine, CG_SHUDElementGameTimeDestroy },
	{ "gametype", 0, },
	{ "itempickup", 0, CG_SHUDElementItemPickupCreate, CG_SHUDElementItemPickupRoutine, CG_SHUDElementItemPickupDestroy },
	{ "itempickupicon", 0, CG_SHUDElementItemPickupIconCreate, CG_SHUDElementItemPickupIconRoutine, CG_SHUDElementItemPickupIconDestroy },
	{ "itemtimers1_icons", 0, },
	{ "itemtimers2_icons", 0, },
	{ "itemtimers3_icons", 0, },
	{ "itemtimers4_icons", 0, },
	{ "itemtimers1_times", 0, },
	{ "itemtimers2_times", 0, },
	{ "itemtimers3_times", 0, },
	{ "itemtimers4_times", 0, },
	{ "keydown_back", 0, },
	{ "keydown_crouch", 0, },
	{ "keydown_forward", 0, },
	{ "keydown_jump", 0, },
	{ "keydown_left", 0, },
	{ "keydown_right", 0, },
	{ "keyup_back", 0, },
	{ "keyup_crouch", 0, },
	{ "keyup_forward", 0, },
	{ "keyup_jump", 0, },
	{ "keyup_left", 0, },
	{ "keyup_right", 0, },
	{ "localtime", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementLocalTimeCreate, CG_SHUDElementLocalTimeRoutine, CG_SHUDElementLocalTimeDestroy },
	{ "multiview", 0, },
	{ "name_nme", 0, CG_SHUDElementNameNMECreate, CG_SHUDElementNameRoutine, CG_SHUDElementNameDestroy  },
	{ "name_own", 0, CG_SHUDElementNameOWNCreate, CG_SHUDElementNameRoutine, CG_SHUDElementNameDestroy  },
	{ "netgraph", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementNGCreate, CG_SHUDElementNGRoutine, CG_SHUDElementNGDestroy },
	{ "netgraphping", SE_IM | SE_SPECT | SE_DEAD, CG_SHUDElementNGPCreate, CG_SHUDElementNGPRoutine, CG_SHUDElementNGPDestroy },
	{ "playerspeed", 0, CG_SHUDElementPlayerSpeedCreate, CG_SHUDElementPlayerSpeedRoutine, CG_SHUDElementPlayerSpeedDestroy },
	{ "powerup1_icon", 0, CG_SHUDElementPwIcon1Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup2_icon", 0, CG_SHUDElementPwIcon2Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup3_icon", 0, CG_SHUDElementPwIcon3Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup4_icon", 0, CG_SHUDElementPwIcon4Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup5_icon", 0, CG_SHUDElementPwIcon5Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup6_icon", 0, CG_SHUDElementPwIcon6Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup7_icon", 0, CG_SHUDElementPwIcon7Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup8_icon", 0, CG_SHUDElementPwIcon8Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup1_time", 0, CG_SHUDElementPwTime1Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup2_time", 0, CG_SHUDElementPwTime2Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup3_time", 0, CG_SHUDElementPwTime3Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup4_time", 0, CG_SHUDElementPwTime4Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup5_time", 0, CG_SHUDElementPwTime5Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup6_time", 0, CG_SHUDElementPwTime6Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup7_time", 0, CG_SHUDElementPwTime7Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "powerup8_time", 0, CG_SHUDElementPwTime8Create, CG_SHUDElementPwRoutine, CG_SHUDElementPwDestroy },
	{ "rankmessage", 0, CG_SHUDElementRankMessageCreate, CG_SHUDElementRankMessageRoutine, CG_SHUDElementRankMessageDestroy},
	{ "recordingdemo", 0, },
	{ "score_limit", 0, CG_SHUDElementScoreMAXCreate, CG_SHUDElementScoreRoutine, CG_SHUDElementScoreDestroy },
	{ "score_nme", 0, CG_SHUDElementScoreNMECreate, CG_SHUDElementScoreRoutine, CG_SHUDElementScoreDestroy },
	{ "score_own", 0, CG_SHUDElementScoreOWNCreate, CG_SHUDElementScoreRoutine, CG_SHUDElementScoreDestroy },
	{ "specmessage", SE_SPECT, CG_SHUDElementSpecMessageCreate, CG_SHUDElementSpecMessageRoutine, CG_SHUDElementSpecMessageDestroy },
	{ "statusbar_armorbar", 0, CG_SHUDElementSBABCreate, CG_SHUDElementSBABRoutine, CG_SHUDElementSBABDestroy },
	{ "statusbar_armorcount", 0, CG_SHUDElementSBACCreate, CG_SHUDElementSBACRoutine, CG_SHUDElementSBACDestroy },
	{ "statusbar_armoricon", 0, CG_SHUDElementSBAICreate, CG_SHUDElementSBAIRoutine, CG_SHUDElementSBAIDestroy },
	{ "statusbar_ammobar", 0, CG_SHUDElementSBAmBCreate, CG_SHUDElementSBAmBRoutine, CG_SHUDElementSBAmBDestroy },
	{ "statusbar_ammocount", 0, CG_SHUDElementSBAmCCreate, CG_SHUDElementSBAmCRoutine, CG_SHUDElementSBAmCDestroy },
	{ "statusbar_ammoicon", 0, CG_SHUDElementSBAmICreate, CG_SHUDElementSBAmIRoutine, CG_SHUDElementSBAmIDestroy },
	{ "statusbar_healthbar", 0, CG_SHUDElementSBHBCreate, CG_SHUDElementSBHBRoutine, CG_SHUDElementSBHBDestroy },
	{ "statusbar_healthcount", 0, CG_SHUDElementSBHCCreate, CG_SHUDElementSBHCRoutine, CG_SHUDElementSBHCDestroy },
	{ "statusbar_healthicon", 0, CG_SHUDElementSBHICreate, CG_SHUDElementSBHIRoutine, CG_SHUDElementSBHIDestroy },
	{ "targetname", 0, CG_SHUDElementTargetNameCreate, CG_SHUDElementTargetNameRoutine, CG_SHUDElementTargetNameDestroy },
	{ "targetstatus", SE_TEAM_ONLY, CG_SHUDElementTargetStatusCreate, CG_SHUDElementTargetStatusRoutine, CG_SHUDElementTargetStatusDestroy },
	{ "teamcount_nme", SE_TEAM_ONLY, CG_SHUDElementTeamCountNMECreate, CG_SHUDElementTeamCountRoutine, CG_SHUDElementTeamCountDestroy },
	{ "teamcount_own", SE_TEAM_ONLY, CG_SHUDElementTeamCountOWNCreate, CG_SHUDElementTeamCountRoutine, CG_SHUDElementTeamCountDestroy },
	{ "teamicon_nme", SE_TEAM_ONLY, },
	{ "teamicon_own", SE_TEAM_ONLY, },
	{ "team1", SE_TEAM_ONLY, CG_SHUDElementTeam1Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team2", SE_TEAM_ONLY, CG_SHUDElementTeam2Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team3", SE_TEAM_ONLY, CG_SHUDElementTeam3Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team4", SE_TEAM_ONLY, CG_SHUDElementTeam4Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team5", SE_TEAM_ONLY, CG_SHUDElementTeam5Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team6", SE_TEAM_ONLY, CG_SHUDElementTeam6Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team7", SE_TEAM_ONLY, CG_SHUDElementTeam7Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team8", SE_TEAM_ONLY, CG_SHUDElementTeam8Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team9", SE_TEAM_ONLY, CG_SHUDElementTeam9Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team10", SE_TEAM_ONLY, CG_SHUDElementTeam10Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team11", SE_TEAM_ONLY, CG_SHUDElementTeam11Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team12", SE_TEAM_ONLY, CG_SHUDElementTeam12Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team13", SE_TEAM_ONLY, CG_SHUDElementTeam13Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team14", SE_TEAM_ONLY, CG_SHUDElementTeam14Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team15", SE_TEAM_ONLY, CG_SHUDElementTeam15Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "team16", SE_TEAM_ONLY, CG_SHUDElementTeam16Create, CG_SHUDElementTeamRoutine, CG_SHUDElementTeamDestroy },
	{ "votemessagearena", 0, },
	{ "votemessageworld", 0, CG_SHUDElementVMWCreate, CG_SHUDElementVMWRoutine, CG_SHUDElementVMWDestroy },
	{ "warmupinfo", 0, },
	{ "weaponlist", 0, CG_SHUDElementWeaponListCreate, CG_SHUDElementWeaponListRoutine, CG_SHUDElementWeaponListDestroy },
	{ "weaponselection", 0, },
	{ "weaponselectionname", 0, },
	{ "chat", 0, },
	{ "gameevents", 0, },
	{ "team1_NME", 0, },
	{ "team2_NME", 0, },
	{ "team3_NME", 0, },
	{ "team4_NME", 0, },
	{ "team5_NME", 0, },
	{ "team6_NME", 0, },
	{ "team7_NME", 0, },
	{ "team8_NME", 0, },
	{ "rewardicons", 0, CG_SHUDElementRewardIconCreate, CG_SHUDElementRewardRoutine, CG_SHUDElementRewardDestroy },
	{ "rewardnumbers", 0, CG_SHUDElementRewardCountCreate, CG_SHUDElementRewardRoutine, CG_SHUDElementRewardDestroy },
	{ "postdecorate", 0, CG_SHUDElementDecorCreate, CG_SHUDElementDecorRoutine, CG_SHUDElementDecorDestroy },
	{ NULL },
};

void CG_SHUDAvailableElementsInit(void)
{
	int i = 0;

	while (superHUDConfigItemElements[i].name)
	{
		superHUDConfigItemElements[i].order = i;
		++i;
	}
}

const superHUDConfigElement_t* CG_SHUDAvailableElementsGet(void)
{
	return &superHUDConfigItemElements[0];
}

superhudGlobalContext_t* CG_SHUDGetContext(void)
{
	return &superhudGlobalContext;
}
