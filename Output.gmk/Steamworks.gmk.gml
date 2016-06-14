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
