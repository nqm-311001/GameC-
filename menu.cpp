#include "Menu.h"


Menu::Menu(float width, float height) {
	t1.loadFromFile("../menu.png");
	sBG.setTexture(t1);
	if (!font.loadFromFile("BarlowCondensed-Bold.ttf")) {}
	menu[0].setFont(font);
	menu[0].setCharacterSize(40);
	menu[0].setFillColor(Color::White);
	menu[0].setString("PLAY");
	menu[0].setPosition(200, 200);


	menu[1].setFont(font);
	menu[1].setCharacterSize(40);
	menu[1].setFillColor(Color::Red);
	menu[1].setString("EXIT");
	menu[1].setPosition(200, 300);
}

void Menu::draw(RenderWindow& window) {
	window.draw(sBG);
	for (int i = 0; i < 2; i++) {
		window.draw(menu[i]);
	}
}

void Menu::setItemIndex() {
	selectedItemIndex = 0;
}
void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(Color::Red);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::White);

	}
}
void Menu::MoveDown() {
	if (selectedItemIndex + 1 < 2) {
		menu[selectedItemIndex].setFillColor(Color::Red);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::White);
	}
}
