// @author YellowAfterlife
// License: MIT https://opensource.org/licenses/mit-license.php

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
#define steam_friends SteamFriends()

#pragma region Callbacks
class steam_callbacks_t {
	public:
	steam_callbacks_t() {};
	STEAM_CALLBACK(steam_callbacks_t, stats_received, UserStatsReceived_t);
	void leaderboard_found(LeaderboardFindResult_t* e, bool failed);
	void leaderboard_score_uploaded(LeaderboardScoreUploaded_t* e, bool failed);
	void leaderboard_scores_downloaded(LeaderboardScoresDownloaded_t* e, bool failed);
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

#pragma region Leaderboard
int steam_leaderboard_status_val = 0;
SteamLeaderboard_t steam_leaderboard_current = 0;
CCallResult<steam_callbacks_t, LeaderboardFindResult_t> steam_leaderboard_found;
void steam_callbacks_t::leaderboard_found(LeaderboardFindResult_t* e, bool failed) {
	if (e->m_bLeaderboardFound) {
		steam_leaderboard_status_val = 1;
		steam_leaderboard_current = e->m_hSteamLeaderboard;
	} else {
		steam_leaderboard_status_val = -1;
		steam_leaderboard_current = 0;
	}
}

/// Starts fetching the given leaderboard. See steam_leaderboard_status
dllx double steam_leaderboard_find(char* name) {
	auto call = steam_user_stats->FindLeaderboard(name);
	steam_leaderboard_found.Set(call, &steam_callbacks, &steam_callbacks_t::leaderboard_found);
	steam_leaderboard_status_val = 0;
	return true;
}

/// (top entry has the lowest score)
dllx double steam_leaderboard_sort_method_ascending() { return 1; }
/// (top entry has the highest score)
dllx double steam_leaderboard_sort_method_descending() { return 1; }
/// (display as-is)
dllx double steam_leaderboard_sort_method_none() { return 0; }

/// (simple numeric score)
dllx double steam_leaderboard_display_type_numeric() { return 1; }
/// (displays time in seconds)
dllx double steam_leaderboard_display_type_seconds() { return 2; }
/// (displays time in milliseconds)
dllx double steam_leaderboard_display_type_milliseconds() { return 3; }
/// (don't display on Steam Community at all)
dllx double steam_leaderboard_display_type_none() { return 0; }

/// Starts creating or fetching (if it already exists) the given leaderboard. See steam_leaderboard_status
dllx double steam_leaderboard_create(char* name, double sort_method, double display_type) {
	ELeaderboardSortMethod sort;
	switch ((int)sort_method) {
		case 1: sort = k_ELeaderboardSortMethodAscending; break;
		case -1: sort = k_ELeaderboardSortMethodDescending; break;
		default: sort = k_ELeaderboardSortMethodNone; break;
	}
	ELeaderboardDisplayType display;
	switch ((int)display_type) {
		case 1: display = k_ELeaderboardDisplayTypeNumeric; break;
		case 2: display = k_ELeaderboardDisplayTypeTimeSeconds; break;
		case 3: display = k_ELeaderboardDisplayTypeTimeMilliSeconds; break;
		default: display = k_ELeaderboardDisplayTypeNone; break;
	}
	auto call = steam_user_stats->FindOrCreateLeaderboard(name, sort, display);
	steam_leaderboard_found.Set(call, &steam_callbacks, &steam_callbacks_t::leaderboard_found);
	steam_leaderboard_status_val = 0;
	return true;
}

/// Returns 0 if in progress, 1 if succeeded, -1 if an error occurred.
dllx double steam_leaderboard_status() {
	return steam_leaderboard_status_val;
}
#pragma endregion

#pragma region Score uploading
int steam_leaderboard_upload_status_val = 0;
int steam_leaderboard_upload_rank_val = 0;
CCallResult<steam_callbacks_t, LeaderboardScoreUploaded_t> steam_leaderboard_score_uploaded;
void steam_callbacks_t::leaderboard_score_uploaded(LeaderboardScoreUploaded_t* e, bool failed) {
	if (!e->m_bSuccess || failed) {
		steam_leaderboard_upload_status_val = -1;
	} else {
		steam_leaderboard_upload_status_val = 1;
		steam_leaderboard_upload_rank_val = e->m_nGlobalRankNew;
	}
}

/// Starts submitting the score to the current (see steam_leaderboard_find) leaderboard. See steam_leaderboard_upload_status
dllx double steam_leaderboard_upload(double score, double keep_best_score) {
	steam_leaderboard_upload_status_val = 0;
	steam_leaderboard_upload_rank_val = -1;
	if (!steam_leaderboard_current) return false;
	auto mt = keep_best_score > 0.5 ? k_ELeaderboardUploadScoreMethodKeepBest : k_ELeaderboardUploadScoreMethodForceUpdate;
	auto call = steam_user_stats->UploadLeaderboardScore(steam_leaderboard_current, mt, (int)score, NULL, 0);
	steam_leaderboard_score_uploaded.Set(call, &steam_callbacks, &steam_callbacks_t::leaderboard_score_uploaded);
	return true;
}

/// Returns 0 if still uploading, 1 if successful, -1 if failed to upload.
dllx double steam_leaderboard_upload_status() {
	return steam_leaderboard_upload_status_val;
}

/// Returns the submitter's global rank on the leaderboard.
dllx double steam_leaderboard_upload_rank() {
	return steam_leaderboard_upload_rank_val;
}
#pragma endregion

#pragma region Score downloading
int steam_leaderboard_download_status_val = 0;
std::vector<LeaderboardEntry_t> steam_leaderboard_entries;
CCallResult<steam_callbacks_t, LeaderboardScoresDownloaded_t> steam_leaderboard_scores_downloaded;
void steam_callbacks_t::leaderboard_scores_downloaded(LeaderboardScoresDownloaded_t* e, bool failed) {
	if (!failed) {
		steam_leaderboard_download_status_val = 1;
		int num = e->m_cEntryCount;
		steam_leaderboard_entries.resize(num);
		for (int i = 0; i < num; i++) {
			steam_user_stats->GetDownloadedLeaderboardEntry(e->m_hSteamLeaderboardEntries, i, &steam_leaderboard_entries[i], NULL, 0);
		}
	} else {
		steam_leaderboard_download_status_val = -1;
	}
}

/// Starts downloading scores from the current (steam_leaderboard_find) leaderboard. See steam_leaderboard_download_status.
dllx double steam_leaderboard_download(double start_index, double end_index) {
	steam_leaderboard_download_status_val = 0;
	steam_leaderboard_entries.clear();
	if (!steam_leaderboard_current) return false;
	auto call = steam_user_stats->DownloadLeaderboardEntries(steam_leaderboard_current, k_ELeaderboardDataRequestGlobal, (int)start_index, (int)end_index);
	steam_leaderboard_scores_downloaded.Set(call, &steam_callbacks, &steam_callbacks_t::leaderboard_scores_downloaded);
	return true;
}

/// Starts downloading scores from the current (steam_leaderboard_find) leaderboard relative to current user's rank. See steam_leaderboard_download_status.
dllx double steam_leaderboard_download_around_user(double range_start, double range_end) {
	steam_leaderboard_download_status_val = 0;
	steam_leaderboard_entries.clear();
	if (!steam_leaderboard_current) return false;
	auto call = steam_user_stats->DownloadLeaderboardEntries(steam_leaderboard_current, k_ELeaderboardDataRequestGlobalAroundUser, (int)range_start, (int)range_end);
	steam_leaderboard_scores_downloaded.Set(call, &steam_callbacks, &steam_callbacks_t::leaderboard_scores_downloaded);
	return true;
}

/// Returns 0 if still downloading, 1 if finished (can use steam_leaderboard_entry_ now), -1 in case of error.
dllx double steam_leaderboard_download_status() {
	return steam_leaderboard_download_status_val;
}

/// Returns the number of downloaded entries.
dllx double steam_leaderboard_entry_count() {
	return steam_leaderboard_entries.size();
}

/// Returns the downloaded entry' score.
dllx double steam_leaderboard_entry_score(double index) {
	int i = (int)index;
	if (i < 0 || i >= (int)steam_leaderboard_entries.size()) return 0;
	return steam_leaderboard_entries[i].m_nScore;
}

/// Returns the downloaded entry' global rank.
dllx double steam_leaderboard_entry_rank(double index) {
	int i = (int)index;
	if (i < 0 || i >= (int)steam_leaderboard_entries.size()) return -1;
	return steam_leaderboard_entries[i].m_nGlobalRank;
}

char* steam_leaderboard_entry_name_buf = (char*)malloc(1);
/// Returns the downloaded entry' submitter' name.
dllx char* steam_leaderboard_entry_name(double index) {
	int i = (int)index;
	if (i < 0 || i >= (int)steam_leaderboard_entries.size()) return "";
	auto name = steam_friends->GetFriendPersonaName(steam_leaderboard_entries[i].m_steamIDUser);
	size_t len = sizeof(char) * (strlen(name) + 1);
	steam_leaderboard_entry_name_buf = (char*)realloc(steam_leaderboard_entry_name_buf, len);
	strcpy(steam_leaderboard_entry_name_buf, name);
	return steam_leaderboard_entry_name_buf;
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
