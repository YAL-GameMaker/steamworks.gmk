# steamworks.gmk
Steamworks SDK support for GameMaker 8.1 and earlier.

## Installation
* Add `Output.gmk/steam_api.dll` to the Included Files (menu: Resources - Included Files).
* Add `Output.gmk/Steamworks.gmk.dll` to the Included Files.
* Create a `steam_appid.txt` file containing your Steam App ID, and add it to the Included Files
	
	Sample file is included in `Output.gmk/steam_appid.txt`.
* Drag `Output.gmk/Steamworks.gmk.gml` onto a GameMaker window with the project open to import the scripts.
* Create an object (say, `obj_steam`),
	* Mark it as persistent
	* Add the following into the **Create** event:
		
		```
		steam_init_dll();
		steam_init(480); // replace `480` with your Steam App ID
		```
		This will initialize Steam API and request the user stats&achievements (if any).
		
	* Add the following into the **Step** event:
		
		```
		steam_update_callbacks();
		```
		This is required by Steam API in order to receive API events.
		
		Should you forget to call this function, the user will only receive achievements after they close the game.
		
	* Add the object into the game's first room (so that it is created on game start).
		
		If the game's first room is a menu, make a separate "init" room that has the object and goes to the actual first room via `room_goto_next()` in **Room Creation Code**.

*	If everything was done correctly, upon launching the game Steam will detect you as playing the game, and you'll be able to use Steam API functions as you wish.

## Usage

Once installed, you can use the included `steam_` scripts to call the supported DLL functions.

Every script includes a short description of what it does.

Script naming closely follows that of [built-in GameMaker-Studio functions](http://docs.yoyogames.com/).

[Official documentation](https://partner.steamgames.com/home/steamworks) should be helpful too.

## Things to keep in mind
*	Steam Overlay (default: Shift+Tab) will not show up unless the game is ran from Steam itself
	
	This is due to pre-GMS versions of GameMaker not being able to comply with the required initialization order.
	
*	Achievements and stats can take a few moments to load. You can check whether they are done loading yet via `steam_stats_ready()` function.

## Meta
Author: Vadim "YellowAfterlife" Dyachenko

License: MIT https://opensource.org/licenses/mit-license.php

## Special thanks

* [Emilios Manolidis](http://emilvdweller.wix.com/), for sponsoring initial development of this library for [Emerge: Cities of the Apocalypse](http://store.steampowered.com/app/457600/).
