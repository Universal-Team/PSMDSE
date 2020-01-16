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

#include "core/gameLoader.hpp"

#include "gui/screens/mainMenu.hpp"
#include "gui/screens/screenCommon.hpp"
#include "gui/screens/titleSelection.hpp"

extern bool exiting;

extern bool touching(touchPosition touch, Structs::ButtonPos button);

std::vector<u64> titleIDs = {
	0x0004000000174400, // EUR.
	0x0004000000174600, // USA.
};

void TitleSelection::Draw(void) const {
 	if (selectMode == 1) {
		DrawVersionSelector();
	} else if (selectMode == 2) {
		DrawRegionSelector();
	}
}

void TitleSelection::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (selectMode == 1) {
		versionLogic(hDown, hHeld, touch);
	} else if (selectMode == 2) {
		regionLogic(hDown, hHeld, touch);
	}
}

void TitleSelection::DrawVersionSelector(void) const
{
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.72f, WHITE, "Select the version of your game.", 400);
	Gui::sprite(sprites_Icon_idx, 37.5, 80, 1.5, 1.5);

	Gui::DrawBottom();
	
	for (int i = 0; i < 2; i++) {
		Gui::Draw_Rect(versionButtons[i].x, versionButtons[i].y, versionButtons[i].w, versionButtons[i].h, UNSELECTED_COLOR);
		if (selectedVersion == i) {
			Gui::drawAnimatedSelector(versionButtons[i].x, versionButtons[i].y, versionButtons[i].w, versionButtons[i].h, .030f, SELECTED_COLOR);
		}
	}

	Gui::sprite(sprites_gameCard_idx, 78, 100);
	Gui::sprite(sprites_sdCard_idx, 198, 100);

	Gui::DrawStringCentered(-10-50, 80, 0.6, WHITE, "Gamecard", 80);
	Gui::DrawStringCentered(110-50, 80, 0.6, WHITE, "Installed", 80);
}

void TitleSelection::versionLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_START) {
		exiting = true;
	}

	if (hDown & KEY_RIGHT || hDown & KEY_R) {
		if (selectedVersion < 1)	selectedVersion++;
	} else if (hDown & KEY_LEFT || hDown & KEY_L) {
		if (selectedVersion > 0)	selectedVersion--;
	}

	if (hDown & KEY_TOUCH) {
		if (touching(touch, versionButtons[0])) {
			selectedVersion = 0;
			selectMode = 2;
		} else if (touching(touch, versionButtons[1])) {
			selectedVersion = 1;
			selectMode = 2;
		}
	}

	if (hDown & KEY_A) {
		selectMode = 2;
	}
}

void TitleSelection::DrawRegionSelector(void) const {
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.72f, WHITE, "Select the region of your game.", 400);
	Gui::sprite(sprites_Icon_idx, 37.5, 80, 1.5, 1.5);

	if (selectedVersion == 0) {
		Gui::sprite(sprites_gameCard_idx, 140, 80, 1.5, 1.5);
	} else if (selectedVersion == 1) {
		Gui::sprite(sprites_sdCard_idx, 140, 80, 1.5, 1.5);
	}


	Gui::DrawBottom();
	
	for (int i = 0; i < 4; i++) {
		Gui::Draw_Rect(regionButtons[i].x, regionButtons[i].y, regionButtons[i].w, regionButtons[i].h, UNSELECTED_COLOR);
		if (selectedRegion == i) {
			Gui::drawAnimatedSelector(regionButtons[i].x, regionButtons[i].y, regionButtons[i].w, regionButtons[i].h, .030f, SELECTED_COLOR);
		}
	}

	Gui::DrawStringCentered(-90-30, 95, 0.6, WHITE, "Japan", 50);
	Gui::DrawStringCentered(-10-30, 95, 0.6, WHITE, "USA", 50);
	Gui::DrawStringCentered(70-30, 95, 0.6, WHITE, "Europe", 50);
	Gui::DrawStringCentered(150-30, 95, 0.6, WHITE, "Korea", 50);

	Gui::sprite(sprites_japan_idx, 18, 120);
	Gui::sprite(sprites_usa_idx, 98, 120);
	Gui::sprite(sprites_europe_idx, 178, 120);
	Gui::sprite(sprites_korea_idx, 258, 120);
}

void TitleSelection::regionLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		selectMode = 1;
	}

	if (hDown & KEY_RIGHT || hDown & KEY_R) {
		if (selectedRegion < 3)	selectedRegion++;
	} else if (hDown & KEY_LEFT || hDown & KEY_L) {
		if (selectedRegion > 0)	selectedRegion--;
	}

	if (hDown & KEY_TOUCH) {
		// JPN.
		if (touching(touch, regionButtons[0])) {
			Msg::NotImplementedYet();
			// USA.
		} else if (touching(touch, regionButtons[1])) {
			if (selectedVersion == 1) {
				if (GameLoader::checkTitle(titleIDs[1])) {
					Gui::setScreen(std::make_unique<MainMenu>());
				}
			} else if (selectedVersion == 0) {
				if (GameLoader::scanCard(titleIDs[1])) {
					Gui::setScreen(std::make_unique<MainMenu>());
				}
			}
			// EUR.
		} else if (touching(touch, regionButtons[2])) {
			if (selectedVersion == 1) {
				if (GameLoader::checkTitle(titleIDs[0])) {
					Gui::setScreen(std::make_unique<MainMenu>());
				}
			} else if (selectedVersion == 0) {
				if (GameLoader::scanCard(titleIDs[0])) {
					Gui::setScreen(std::make_unique<MainMenu>());
				}
			}
			// KOR.
		} else if (touching(touch, regionButtons[3])) {
			Msg::NotImplementedYet();
		}
	}

	if (hDown & KEY_A) {
		// JPN.
		if (selectedVersion == 1 && selectedRegion == 0) {
			Msg::NotImplementedYet();
		} else if (selectedVersion == 0 && selectedRegion == 0) { 
			Msg::NotImplementedYet();

		// USA.
		} else if (selectedVersion == 1 && selectedRegion == 1) {
			if (GameLoader::checkTitle(titleIDs[1])) {
				Gui::setScreen(std::make_unique<MainMenu>());
			}
		} else if (selectedVersion == 0 && selectedRegion == 1) {
			if (GameLoader::scanCard(titleIDs[1])) {
				Gui::setScreen(std::make_unique<MainMenu>());
			}

		// EUR.
		} else if (selectedVersion == 1 && selectedRegion == 2) {
			if (GameLoader::checkTitle(titleIDs[0])) {
				Gui::setScreen(std::make_unique<MainMenu>());
			}
		} else if (selectedVersion == 0 && selectedRegion == 2) {
			if (GameLoader::scanCard(titleIDs[0])) {
				Gui::setScreen(std::make_unique<MainMenu>());
			}

		// KOR.
		} else 	if (selectedVersion == 1 && selectedRegion == 3) {
			Msg::NotImplementedYet();
		} else if (selectedVersion == 0 && selectedRegion == 3) { 
			Msg::NotImplementedYet();
		}
	}
}