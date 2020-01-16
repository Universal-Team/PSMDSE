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

#include "gui/gui.hpp"
#include "gui/msg.hpp"

#include <algorithm>
#include <vector>


u64 currentID;
u32 currentLowID;
u32 currentHighID;
u32 currentUniqueID;
FS_MediaType currentMedia;

bool GameLoader::checkTitle(u64 TitleID) {
	Result res = 0;
	static u32 titleCount;

	res = AM_GetTitleCount(MEDIATYPE_SD, &titleCount);
	if (R_FAILED(res))
	{
		return false; // cause failed.
	}

	std::vector<u64> ID;
	ID.resize(titleCount);

	// Get Title List.
	res = AM_GetTitleList(nullptr, MEDIATYPE_SD, titleCount, &ID[0]);
	if (R_FAILED(res))
	{
		return false; // cause failed.
	}
	// Check, if TitleID matches.
	if (std::find(ID.begin(), ID.end(), TitleID) != ID.end()) {
		currentID = TitleID;
		currentLowID = (u32)currentID;
		currentHighID = (u32)(currentID >> 32);
		currentUniqueID = (currentLowID >> 8);
		currentMedia = MEDIATYPE_SD;
		return true; // cause is found.
	} else {
		Msg::DisplayWarnMsg("Title not found!");
		return false; // cause isn't found.
	}
}

bool GameLoader::scanCard(u64 TitleID)
{
	Result res = 0;
	u32 titleCount  = 0;
	// check for the cartridge.
	FS_CardType cardType;
	res = FSUSER_GetCardType(&cardType);
	if (R_SUCCEEDED(res))
	{
		if (cardType == CARD_CTR)
		{
			res = AM_GetTitleCount(MEDIATYPE_GAME_CARD, &titleCount);
			if (R_SUCCEEDED(res) && titleCount > 0)
			{
				std::vector<u64> ID;
				ID.resize(titleCount);
				res = AM_GetTitleList(NULL, MEDIATYPE_GAME_CARD, titleCount, &ID[0]);

				// check if this id is in our list
				if (R_SUCCEEDED(res) && std::find(ID.begin(), ID.end(), TitleID) != ID.end())
				{
					currentID = TitleID;
					currentLowID = (u32)currentID;
					currentHighID = (u32)(currentID >> 32);
					currentUniqueID = (currentLowID >> 8);
					currentMedia = MEDIATYPE_GAME_CARD;
					return true; // cause is found.
				} else {
					Msg::DisplayWarnMsg("Title not found!");
					return false; // cause isn't found.
				}
			} else {
				Msg::DisplayWarnMsg("Title not found!");
				return false; // cause isn't found.
			}
		} else {
			Msg::DisplayWarnMsg("Title not found!");
			return false; // cause isn't found.
		}
	} else {
		Msg::DisplayWarnMsg("Title not found!");
		return false; // cause isn't found.
	}
}