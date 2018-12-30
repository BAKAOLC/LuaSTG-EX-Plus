#include "AppFrame.h"
#include "lstgsteam.h"

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
Achievement_t g_rgAchievements[] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};


void SteamHost::Frame()
{

}
void SteamHost::OnUserStatsReceived(UserStatsReceived_t *pCallback)
{
	if (!m_pSteamUserStats)
		return;

	// we may get callbacks for other games' stats arriving, ignore them
	if (m_GameID.ToUint64() == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString(L"Received stats and achievements from Steam\n");

			m_bStatsValid = true;

			// load achievements
			for (int iAch = 0; iAch < ARRAYSIZE(g_rgAchievements); ++iAch)
			{
				Achievement_t &ach = g_rgAchievements[iAch];
				m_pSteamUserStats->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
				
			}

			// load stats
			m_pSteamUserStats->GetStat("NumGames", &m_nTotalGamesPlayed);
			m_pSteamUserStats->GetStat("NumWins", &m_nTotalNumWins);
			m_pSteamUserStats->GetStat("NumLosses", &m_nTotalNumLosses);
			m_pSteamUserStats->GetStat("FeetTraveled", &m_flTotalFeetTraveled);
			m_pSteamUserStats->GetStat("MaxFeetTraveled", &m_flMaxFeetTraveled);
			m_pSteamUserStats->GetStat("AverageSpeed", &m_flAverageSpeed);
		}
		else
		{
			
		}
	}
}