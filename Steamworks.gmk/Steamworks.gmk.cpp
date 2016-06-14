// @author YellowAfterlife

#include "./../Steamworks/public/steam/steam_api.h"
#include <vector>

#define dllx extern "C" __declspec(dllexport)
#define trace(...) { printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
bool steam_is_initialized = false;
uint32 steam_app_id;
//
char* cpc2pc_buf = NULL;
size_t cpc2pc_len = 0;
/// const char* -> char* convertor. Reuses a static buffer.
char* cpc2pc(const char* s) {
	size_t n = strlen(s) + 1;
	if (cpc2pc_len < n) {
		if (cpc2pc_buf != NULL) delete cpc2pc_buf;
		cpc2pc_buf = new char[n];
		cpc2pc_len = n;
	}
	strcpy(cpc2pc_buf, s);
	return cpc2pc_buf;
}
///
dllx double steam_get_app_id() {
	return steam_app_id;
}

#define steam_user_stats SteamUserStats()

#pragma region Callbacks
class steam_callbacks_t {
	public:
	steam_callbacks_t() {};
	STEAM_CALLBACK(steam_callbacks_t, stats_received, UserStatsReceived_t);
} steam_callbacks;
#pragma endregion

#pragma region Stats
bool steam_stats_are_ready = false;
void steam_callbacks_t::stats_received(UserStatsReceived_t* e) {
	if (e->m_nGameID == steam_app_id && e->m_eResult == k_EResultOK) {
		steam_stats_are_ready = true;
	}
}

/// Requests the user's stats. DLL does this automatically for you at init.
dllx double steam_stats_request() {
	if (steam_user_stats) {
		return steam_user_stats->RequestCurrentStats();
	} else return false;
}

/// Returns whether stats have been received and can be worked with.
dllx double steam_stats_ready() {
	return steam_stats_are_ready;
}

///
dllx double steam_get_stat_float(char* name) {
	if (steam_user_stats) {
		float out;
		if (steam_user_stats->GetStat(name, &out)) return out;
	}
	return 0;
}

///
dllx double steam_get_stat_int(char* name) {
	if (steam_user_stats) {
		int32 out;
		if (steam_user_stats->GetStat(name, &out)) return out;
	}
	return 0;
}

///
dllx double steam_set_stat_float(char* name, double value) {
	if (steam_user_stats) {
		return steam_user_stats->SetStat(name, (float)value) && steam_user_stats->StoreStats();
	} else return false;
}

///
dllx double steam_set_stat_int(char* name, double value) {
	if (steam_user_stats) {
		return steam_user_stats->SetStat(name, (int32)value) && steam_user_stats->StoreStats();
	} else return false;
}
#pragma endregion

#pragma region Achievements

/// Returns whether the given achievement is already obtained.
dllx double steam_achievement_status(char* name) {
	if (steam_user_stats && steam_stats_are_ready) {
		bool out = false;
		steam_user_stats->GetAchievement(name, &out);
		return out;
	} else return false;
}

/// "Obtains" the given achievement.
dllx double steam_achievement_obtain(char* name) {
	if (steam_user_stats && steam_stats_are_ready) {
		steam_user_stats->SetAchievement(name);
		return steam_user_stats->StoreStats();
	} else return false;
}

/// "Un-obtains" the given achievement.
dllx double steam_achievement_clear(char* name) {
	if (steam_user_stats && steam_stats_are_ready) {
		steam_user_stats->ClearAchievement(name);
		return steam_user_stats->StoreStats();
	} else return false;
}

/// Retrieves an attribute ("name", "desc", "hidden") for an achievement.
dllx char* steam_achievement_get_attr(char* name, char* attr) {
	const char* r = steam_user_stats->GetAchievementDisplayAttribute(name, attr);
	return cpc2pc(r);
}
#pragma endregion

/// Initializes Steam API. Returns 1 if successful, 0 on failure, -1 if the game needs to restart first.
dllx double steam_init(double app_id) {
	steam_app_id = (uint32)app_id;
	if (SteamAPI_RestartAppIfNecessary(-1)) {
		return -1;
	}
	if (!SteamAPI_Init()) {
		return 0;
	}
	steam_is_initialized = true;
	steam_stats_request();
	return 1;
}

/// Returns whether Steam API is initialized and should be working correctly.
dllx double steam_initialized() {
	return steam_is_initialized;
}

/// Updates Steam API events. Should be called once per game frame.
dllx double steam_update_callbacks() {
	SteamAPI_RunCallbacks();
	return true;
}

// [this is only to verify that the DLL exists as such]
dllx double steam_preinit() {
	return true;
}
