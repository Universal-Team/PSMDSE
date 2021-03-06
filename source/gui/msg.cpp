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

#include "common.hpp"

// Display a Message, which needs to be confirmed with A/B.
bool Msg::promptMsg2(std::string promptMsg)
{
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::Draw_Rect(0, 80, 400, 80, DARKER_COLOR);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.72f, promptMsg))/2, 0.6f, WHITE, promptMsg, 390, 70);
	Gui::DrawStringCentered(0, 214, 0.72f, WHITE, "Press A to confirm, B to cancel.", 390);
	GFX::DrawBottom();
	C3D_FrameEnd(0);

	while(1)
	{
		gspWaitForVBlank();
		hidScanInput();
		if(hidKeysDown() & KEY_A) {
			return true;
		} else if(hidKeysDown() & KEY_B) {
			return false;
		}
	}
}

bool Msg::promptMsg(std::string msg) {
	return Msg::promptMsg2(msg);
}

// Displays a Warn Message.
void Msg::DisplayWarnMsg(std::string Text)
{
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::Draw_Rect(0, 80, 400, 80, DARKER_COLOR);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.72f, Text))/2, 0.72f, WHITE, Text, 395, 70);
	GFX::DrawBottom();
	C3D_FrameEnd(0);
	for (int i = 0; i < 60*2; i++) {
		gspWaitForVBlank();
	}
}

// Displays a Warn Message. This is mostly be used for things with more text.
void Msg::DisplayWarnMsg2(std::string Text)
{
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::Draw_Rect(0, 80, 400, 80, DARKER_COLOR);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.72f, Text))/2, 0.72f, WHITE, Text, 395, 70);
	GFX::DrawBottom();
	C3D_FrameEnd(0);
	for (int i = 0; i < 60*2; i++) {
		gspWaitForVBlank();
	}
}

// Display a Message, which can be skipped with A.
void Msg::DisplayWaitMsg(std::string waitMsg, ...)
{
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::Draw_Rect(0, 80, 400, 80, DARKER_COLOR);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.72f, waitMsg))/2, 0.72f, WHITE, waitMsg, 390, 70);
	Gui::DrawStringCentered(0, 214, 0.72f, WHITE, "Press A to continue.", 390);
	GFX::DrawBottom();
	C3D_FrameEnd(0);

	while(1)
	{
		hidScanInput();
		if(hidKeysDown() & KEY_A)
			break;
	}
}

void Msg::HelperBox(std::string Msg) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 240, DIM);
	Gui::Draw_Rect(0, 27, 400, 187, DARKER_COLOR); // Outline.
	Gui::Draw_Rect(2, 29, 396, 183, LIGHT_COLOR); // BG.
	Gui::DrawString(10, 42, 0.45f, WHITE, Msg, 380);
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 240, DIM);
	C3D_FrameEnd(0);
}

void Msg::DisplayMsg(std::string Message) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	Gui::Draw_Rect(0, 80, 400, 80, DARKER_COLOR);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.72f, Message))/2, 0.72f, WHITE, Message, 390, 70);
	GFX::DrawBottom();
	C3D_FrameEnd(0);
}


void Msg::NotImplementedYet(void) {
	Msg::DisplayWarnMsg("This is not implemented yet!");
}