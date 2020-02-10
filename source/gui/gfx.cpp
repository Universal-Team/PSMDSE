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

#include "gfx.hpp"
#include "screenCommon.hpp"

// Include all spritesheet's maybe for their draw function here?
extern C2D_SpriteSheet sprites;

void GFX::DrawTop(bool useBars) {
	Gui::ScreenDraw(Top);
	if (useBars) {
		Gui::Draw_Rect(0, 0, 400, 30, DARKER_COLOR);
		Gui::Draw_Rect(0, 30, 400, 180, LIGHT_COLOR);
		Gui::Draw_Rect(0, 210, 400, 30, DARKER_COLOR);
	} else {
		Gui::Draw_Rect(0, 0, 400, 240, LIGHT_COLOR);
	}
}

void GFX::DrawBottom(bool useBars) {
	Gui::ScreenDraw(Bottom);
	if (useBars) {
		Gui::Draw_Rect(0, 0, 320, 30, DARKER_COLOR);
		Gui::Draw_Rect(0, 30, 320, 180, LIGHT_COLOR);
		Gui::Draw_Rect(0, 210, 320, 30, DARKER_COLOR);
	} else {
		Gui::Draw_Rect(0, 0, 320, 240, LIGHT_COLOR);
	}
}

void GFX::DrawFileBrowseBG(bool isTop) {
	if (isTop == true) {
		Gui::ScreenDraw(Top);
		Gui::Draw_Rect(0, 0, 400, 27, DARKER_COLOR);
		Gui::Draw_Rect(0, 27, 400, 31, LIGHT_COLOR);
		Gui::Draw_Rect(0, 58, 400, 31, LIGHTER_COLOR);
		Gui::Draw_Rect(0, 89, 400, 31, LIGHT_COLOR);
		Gui::Draw_Rect(0, 120, 400, 31, LIGHTER_COLOR);
		Gui::Draw_Rect(0, 151, 400, 31, LIGHT_COLOR);
		Gui::Draw_Rect(0, 182, 400, 31, LIGHTER_COLOR);
		Gui::Draw_Rect(0, 213, 400, 27, DARKER_COLOR);
	} else {
		Gui::ScreenDraw(Bottom);
		Gui::Draw_Rect(0, 0, 320, 27, DARKER_COLOR);
		Gui::Draw_Rect(0, 27, 320, 31, LIGHT_COLOR);
		Gui::Draw_Rect(0, 58, 320, 31, LIGHTER_COLOR);
		Gui::Draw_Rect(0, 89, 320, 31, LIGHT_COLOR);
		Gui::Draw_Rect(0, 120, 320, 31, LIGHTER_COLOR);
		Gui::Draw_Rect(0, 151, 320, 31, LIGHT_COLOR);
		Gui::Draw_Rect(0, 182, 320, 31, LIGHTER_COLOR);
		Gui::Draw_Rect(0, 213, 320, 27, DARKER_COLOR);
	}
}

void GFX::DrawSprite(int img, int x, int y, float ScaleX, float ScaleY)
{
	Gui::DrawSprite(sprites, img, x, y, ScaleX, ScaleY);
}

void GFX::DrawSpriteBlend(int img, int x, int y, u32 color, float ScaleX, float ScaleY)
{
	C2D_ImageTint tint;
	C2D_SetImageTint(&tint, C2D_TopLeft, color, 0.5);
	C2D_SetImageTint(&tint, C2D_TopRight, color, 0.5);
	C2D_SetImageTint(&tint, C2D_BotLeft, color, 0.5);
	C2D_SetImageTint(&tint, C2D_BotRight, color, 0.5);
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, img), x, y, 0.5f, &tint, ScaleX, ScaleY);
}