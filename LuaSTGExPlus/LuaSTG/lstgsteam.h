#pragma once

enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_HEAVY_FIRE = 2,
	ACH_TRAVEL_FAR_ACCUM = 3,
	ACH_TRAVEL_FAR_SINGLE = 4,
};

struct Achievement_t
{
	EAchievements m_eAchievementID;
	const char *m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};
#include "steam_api.h"
#include "isteamuserstats.h"
#include "isteamremotestorage.h"
#include "isteammatchmaking.h"
#include "steam_gameserver.h"
#include "isteamuser.h"

class SteamHost{
public:
	ISteamUser *m_pSteamUser;
	ISteamUserStats *m_pSteamUserStats;

	// Did we get the stats from Steam?
	bool m_bRequestedStats;
	bool m_bStatsValid;

	// Persisted Stat details
	int m_nTotalGamesPlayed;
	int m_nTotalNumWins;
	int m_nTotalNumLosses;
	float m_flTotalFeetTraveled;
	float m_flMaxFeetTraveled;
	float m_flAverageSpeed;

	CGameID m_GameID;

	STEAM_CALLBACK(SteamHost, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
	STEAM_CALLBACK(SteamHost, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
	STEAM_CALLBACK(SteamHost, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);


	void Frame();
};