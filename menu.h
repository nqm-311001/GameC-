#pragma once

#include<SFML/Graphics.hpp>
using namespace sf;

class Menu
{
public:
	Menu(float w, float h);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void setItemIndex();
	int GetPressedItem() {
		return selectedItemIndex;
	}

private:
	int selectedItemIndex;
	Font font;
	Text menu[2];
	Texture t1;
	Sprite sBG;
};
