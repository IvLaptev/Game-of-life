#include "Counter.h"

Counter::Counter(double ratio) {
	texture.loadFromFile(START_SCREEN);
	std::vector<IntRect> coordinates = {
		IntRect(21, 320, 13, 34),
		IntRect(34, 320, 21, 34),
		IntRect(55, 320, 21, 34),
		IntRect(76, 320, 21, 34),
		IntRect(97, 320, 21, 34),
		IntRect(118, 320, 21, 34),
		IntRect(139, 320, 21, 34),
		IntRect(160, 320, 21, 34),
		IntRect(181, 320, 21, 34)
	};

	for (int i = 0; i < 9; i++) {
		font[i].setTexture(texture);
		font[i].setTextureRect(coordinates[i]);
		font[i].setScale(ratio, ratio);
	}

	this->ratio = ratio;
	count = 0;
}

void Counter::setPosition(Vector2f position) {
	font[0].setPosition(position.x + 3, position.y);
	for (int i = 1; i < 9; i++) {
		font[i].setPosition(position);
	}
}

void Counter::increase() {
	if (count < 9 - 1) {
		count++;
	}
}

void Counter::decrease() {
	if (count > 0) {
		count--;
	}
}

void Counter::draw(RenderWindow &window) {
	window.draw(font[count]);
}

Counter::~Counter(){
}
