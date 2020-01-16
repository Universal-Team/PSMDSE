/*
*   This file is part of PSMDSE
*   Copyright (C) 2020 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, StackZ, TotallyNotGuy
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "common/structs.hpp"

#include "core/gameLoader.hpp"

#include "gui/gui.hpp"
#include "gui/msg.hpp"

#include "gui/screens/screenCommon.hpp"
#include "gui/screens/titleSelection.hpp"

#include <3ds.h>
#include <dirent.h>

// Set to 1, if testing some stuff. Leave to 0, if normal use.
int test = 0;
// If true -> Exit PSMDSE.
bool exiting = false;

// Touch Touch!
touchPosition touch;

u32 DARKER_COLOR, LIGHT_COLOR, LIGHTER_COLOR, SELECTED_COLOR, UNSELECTED_COLOR; // C010r Typ3s.

// If button Position pressed -> Do something.
bool touching(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))
		return true;
	else
		return false;
}

void TestStuff(void)
{
	if (test == 1) {
		// Currently nothing to test.
	}
}

int main()
{
	gfxInitDefault();
	romfsInit();
	Gui::init();
	// make folders if they don't exist
	mkdir("sdmc:/3ds", 0777);	// For DSP dump
	mkdir("sdmc:/3ds/PSMDSE", 0777); // main Path.
	amInit();
	cfguInit();
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users

	DARKER_COLOR = DARKER_BLUE;
	LIGHT_COLOR = LIGHT_BLUE;
	LIGHTER_COLOR = LIGHTER_BLUE;
	SELECTED_COLOR = SELECTED_BLUE;
	UNSELECTED_COLOR = UNSELECTED_BLUE;

	TestStuff();
	
	// Set the Screen to the Title Selection.
	Gui::setScreen(std::make_unique<TitleSelection>());

	// Loop as long as the status is not exit
	while (aptMainLoop() && !exiting)
	{
		hidScanInput();
		u32 hHeld = hidKeysHeld();
		u32 hDown = hidKeysDown();
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, BLACK);
		C2D_TargetClear(bottom, BLACK);
		Gui::clearTextBufs();
		Gui::mainLoop(hDown, hHeld, touch);
		C3D_FrameEnd(0);
	}

	// Exit every process.
	cfguExit();
	amExit();
	Gui::exit();
	gfxExit();
	romfsExit();
	return 0;
}