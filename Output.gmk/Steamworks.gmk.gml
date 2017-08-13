#define steam_init_dll
// Steamworks.gmk.dll:
global.g_steam_get_app_id = external_define("Steamworks.gmk.dll", "steam_get_app_id", dll_stdcall, ty_real, 0);
global.g_steam_stats_request = external_define("Steamworks.gmk.dll", "steam_stats_request", dll_stdcall, ty_real, 0);
global.g_steam_stats_ready = external_define("Steamworks.gmk.dll", "steam_stats_ready", dll_stdcall, ty_real, 0);
global.g_steam_get_stat_float = external_define("Steamworks.gmk.dll", "steam_get_stat_float", dll_stdcall, ty_real, 1, ty_string);
global.g_steam_get_stat_int = external_define("Steamworks.gmk.dll", "steam_get_stat_int", dll_stdcall, ty_real, 1, ty_string);
global.g_steam_set_stat_float = external_define("Steamworks.gmk.dll", "steam_set_stat_float", dll_stdcall, ty_real, 2, ty_string, ty_real);
global.g_steam_set_stat_int = external_define("Steamworks.gmk.dll", "steam_set_stat_int", dll_stdcall, ty_real, 2, ty_string, ty_real);
global.g_steam_achievement_status = external_define("Steamworks.gmk.dll", "steam_achievement_status", dll_stdcall, ty_real, 1, ty_string);
global.g_steam_achievement_obtain = external_define("Steamworks.gmk.dll", "steam_achievement_obtain", dll_stdcall, ty_real, 1, ty_string);
global.g_steam_achievement_clear = external_define("Steamworks.gmk.dll", "steam_achievement_clear", dll_stdcall, ty_real, 1, ty_string);
global.g_steam_achievement_get_attr = external_define("Steamworks.gmk.dll", "steam_achievement_get_attr", dll_stdcall, ty_string, 2, ty_string, ty_string);
global.g_steam_leaderboard_find = external_define("Steamworks.gmk.dll", "steam_leaderboard_find", dll_stdcall, ty_real, 1, ty_string);
global.g_steam_leaderboard_sort_method_ascending = external_define("Steamworks.gmk.dll", "steam_leaderboard_sort_method_ascending", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_sort_method_descending = external_define("Steamworks.gmk.dll", "steam_leaderboard_sort_method_descending", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_sort_method_none = external_define("Steamworks.gmk.dll", "steam_leaderboard_sort_method_none", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_display_type_numeric = external_define("Steamworks.gmk.dll", "steam_leaderboard_display_type_numeric", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_display_type_seconds = external_define("Steamworks.gmk.dll", "steam_leaderboard_display_type_seconds", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_display_type_milliseconds = external_define("Steamworks.gmk.dll", "steam_leaderboard_display_type_milliseconds", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_display_type_none = external_define("Steamworks.gmk.dll", "steam_leaderboard_display_type_none", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_create = external_define("Steamworks.gmk.dll", "steam_leaderboard_create", dll_stdcall, ty_real, 3, ty_string, ty_real, ty_real);
global.g_steam_leaderboard_status = external_define("Steamworks.gmk.dll", "steam_leaderboard_status", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_upload = external_define("Steamworks.gmk.dll", "steam_leaderboard_upload", dll_stdcall, ty_real, 2, ty_real, ty_real);
global.g_steam_leaderboard_upload_status = external_define("Steamworks.gmk.dll", "steam_leaderboard_upload_status", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_upload_rank = external_define("Steamworks.gmk.dll", "steam_leaderboard_upload_rank", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_download = external_define("Steamworks.gmk.dll", "steam_leaderboard_download", dll_stdcall, ty_real, 2, ty_real, ty_real);
global.g_steam_leaderboard_download_around_user = external_define("Steamworks.gmk.dll", "steam_leaderboard_download_around_user", dll_stdcall, ty_real, 2, ty_real, ty_real);
global.g_steam_leaderboard_download_status = external_define("Steamworks.gmk.dll", "steam_leaderboard_download_status", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_entry_count = external_define("Steamworks.gmk.dll", "steam_leaderboard_entry_count", dll_stdcall, ty_real, 0);
global.g_steam_leaderboard_entry_score = external_define("Steamworks.gmk.dll", "steam_leaderboard_entry_score", dll_stdcall, ty_real, 1, ty_real);
global.g_steam_leaderboard_entry_rank = external_define("Steamworks.gmk.dll", "steam_leaderboard_entry_rank", dll_stdcall, ty_real, 1, ty_real);
global.g_steam_leaderboard_entry_name = external_define("Steamworks.gmk.dll", "steam_leaderboard_entry_name", dll_stdcall, ty_string, 1, ty_real);
global.g_steam_init = external_define("Steamworks.gmk.dll", "steam_init", dll_stdcall, ty_real, 1, ty_real);
global.g_steam_initialized = external_define("Steamworks.gmk.dll", "steam_initialized", dll_stdcall, ty_real, 0);
global.g_steam_update_callbacks = external_define("Steamworks.gmk.dll", "steam_update_callbacks", dll_stdcall, ty_real, 0);
global.g_steam_preinit = external_define("Steamworks.gmk.dll", "steam_preinit", dll_stdcall, ty_real, 0);
steam_preinit();

#define steam_get_app_id
/// steam_get_app_id()
return external_call(global.g_steam_get_app_id);

#define steam_stats_request
/// steam_stats_request() : Requests the user's stats. DLL does this automatically for you at init.
return external_call(global.g_steam_stats_request);

#define steam_stats_ready
/// steam_stats_ready() : Returns whether stats have been received and can be worked with.
return external_call(global.g_steam_stats_ready);

#define steam_get_stat_float
/// steam_get_stat_float(name)
return external_call(global.g_steam_get_stat_float, argument0);

#define steam_get_stat_int
/// steam_get_stat_int(name)
return external_call(global.g_steam_get_stat_int, argument0);

#define steam_set_stat_float
/// steam_set_stat_float(name, value)
return external_call(global.g_steam_set_stat_float, argument0, argument1);

#define steam_set_stat_int
/// steam_set_stat_int(name, value)
return external_call(global.g_steam_set_stat_int, argument0, argument1);

#define steam_achievement_status
/// steam_achievement_status(name) : Returns whether the given achievement is already obtained.
return external_call(global.g_steam_achievement_status, argument0);

#define steam_achievement_obtain
/// steam_achievement_obtain(name) : "Obtains" the given achievement.
return external_call(global.g_steam_achievement_obtain, argument0);

#define steam_achievement_clear
/// steam_achievement_clear(name) : "Un-obtains" the given achievement.
return external_call(global.g_steam_achievement_clear, argument0);

#define steam_achievement_get_attr
/// steam_achievement_get_attr(name, attr) : Retrieves an attribute ("name", "desc", "hidden") for an achievement.
return external_call(global.g_steam_achievement_get_attr, argument0, argument1);

#define steam_leaderboard_find
/// steam_leaderboard_find(name) : Starts fetching the given leaderboard. See steam_leaderboard_status
return external_call(global.g_steam_leaderboard_find, argument0);

#define steam_leaderboard_sort_method_ascending
/// steam_leaderboard_sort_method_ascending() : (top entry has the lowest score)
return external_call(global.g_steam_leaderboard_sort_method_ascending);

#define steam_leaderboard_sort_method_descending
/// steam_leaderboard_sort_method_descending() : (top entry has the highest score)
return external_call(global.g_steam_leaderboard_sort_method_descending);

#define steam_leaderboard_sort_method_none
/// steam_leaderboard_sort_method_none() : (display as-is)
return external_call(global.g_steam_leaderboard_sort_method_none);

#define steam_leaderboard_display_type_numeric
/// steam_leaderboard_display_type_numeric() : (simple numeric score)
return external_call(global.g_steam_leaderboard_display_type_numeric);

#define steam_leaderboard_display_type_seconds
/// steam_leaderboard_display_type_seconds() : (displays time in seconds)
return external_call(global.g_steam_leaderboard_display_type_seconds);

#define steam_leaderboard_display_type_milliseconds
/// steam_leaderboard_display_type_milliseconds() : (displays time in milliseconds)
return external_call(global.g_steam_leaderboard_display_type_milliseconds);

#define steam_leaderboard_display_type_none
/// steam_leaderboard_display_type_none() : (don't display on Steam Community at all)
return external_call(global.g_steam_leaderboard_display_type_none);

#define steam_leaderboard_create
/// steam_leaderboard_create(name, sort_method, display_type) : Starts creating or fetching (if it already exists) the given leaderboard. See steam_leaderboard_status
return external_call(global.g_steam_leaderboard_create, argument0, argument1, argument2);

#define steam_leaderboard_status
/// steam_leaderboard_status() : Returns 0 if in progress, 1 if succeeded, -1 if an error occurred.
return external_call(global.g_steam_leaderboard_status);

#define steam_leaderboard_upload
/// steam_leaderboard_upload(score, keep_best_score) : Starts submitting the score to the current (see steam_leaderboard_find) leaderboard. See steam_leaderboard_upload_status
return external_call(global.g_steam_leaderboard_upload, argument0, argument1);

#define steam_leaderboard_upload_status
/// steam_leaderboard_upload_status() : Returns 0 if still uploading, 1 if successful, -1 if failed to upload.
return external_call(global.g_steam_leaderboard_upload_status);

#define steam_leaderboard_upload_rank
/// steam_leaderboard_upload_rank() : Returns the submitter's global rank on the leaderboard.
return external_call(global.g_steam_leaderboard_upload_rank);

#define steam_leaderboard_download
/// steam_leaderboard_download(start_index, end_index) : Starts downloading scores from the current (steam_leaderboard_find) leaderboard. See steam_leaderboard_download_status.
return external_call(global.g_steam_leaderboard_download, argument0, argument1);

#define steam_leaderboard_download_around_user
/// steam_leaderboard_download_around_user(range_start, range_end) : Starts downloading scores from the current (steam_leaderboard_find) leaderboard relative to current user's rank. See steam_leaderboard_download_status.
return external_call(global.g_steam_leaderboard_download_around_user, argument0, argument1);

#define steam_leaderboard_download_status
/// steam_leaderboard_download_status() : Returns 0 if still downloading, 1 if finished (can use steam_leaderboard_entry_ now), -1 in case of error.
return external_call(global.g_steam_leaderboard_download_status);

#define steam_leaderboard_entry_count
/// steam_leaderboard_entry_count() : Returns the number of downloaded entries.
return external_call(global.g_steam_leaderboard_entry_count);

#define steam_leaderboard_entry_score
/// steam_leaderboard_entry_score(index) : Returns the downloaded entry' score.
return external_call(global.g_steam_leaderboard_entry_score, argument0);

#define steam_leaderboard_entry_rank
/// steam_leaderboard_entry_rank(index) : Returns the downloaded entry' global rank.
return external_call(global.g_steam_leaderboard_entry_rank, argument0);

#define steam_leaderboard_entry_name
/// steam_leaderboard_entry_name(index) : Returns the downloaded entry' submitter' name.
return external_call(global.g_steam_leaderboard_entry_name, argument0);

#define steam_init
/// steam_init(app_id) : Initializes Steam API. Returns 1 if successful, 0 on failure, -1 if the game needs to restart first.
return external_call(global.g_steam_init, argument0);

#define steam_initialized
/// steam_initialized() : Returns whether Steam API is initialized and should be working correctly.
return external_call(global.g_steam_initialized);

#define steam_update_callbacks
/// steam_update_callbacks() : Updates Steam API events. Should be called once per game frame.
return external_call(global.g_steam_update_callbacks);

#define steam_preinit
return external_call(global.g_steam_preinit);
