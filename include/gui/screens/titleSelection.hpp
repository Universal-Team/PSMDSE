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

#ifndef TITLESELECTION_HPP
#define TITLESELECTION_HPP

#include "common/structs.hpp"

#include "core/gameLoader.hpp"

#include "gui/screens/screen.hpp"

#include <vector>

class TitleSelection : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	// Screen Modes Draws.
	void DrawVersionSelector(void) const;
	void DrawRegionSelector(void) const;
	// Screen Mode Logics.
	void versionLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void regionLogic(u32 hDown, u32 hHeld, touchPosition touch);

	// Selectors.
	int selectedVersion = 0;
	int selectedRegion = 0;
	int selectMode = 1;

	std::vector<Structs::ButtonPos> versionButtons = {		
		{50, 70, 100, 100, -1}, // Card.
		{170, 70, 100, 100, -1}, // SD.
	};
	std::vector<Structs::ButtonPos> regionButtons = {		
		{10, 70, 60, 100, -1}, // Japanese.
		{90, 70, 60, 100, -1}, // USA.
		{170, 70, 60, 100, -1}, // Europe.
		{250, 70, 60, 100, -1}, // Korean.
	};
};

#endif