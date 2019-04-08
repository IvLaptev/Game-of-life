#include "TextBox.h"

TextBox::TextBox(Texture &texture, bool active) {
	std::vector<IntRect> coordinates = {
		IntRect(0, 320, 21, 34),
		IntRect(21, 320, 13, 34),
		IntRect(34, 320, 21, 34),
		IntRect(55, 320, 21, 34),
		IntRect(76, 320, 21, 34),
		IntRect(97, 320, 21, 34),
		IntRect(118, 320, 21, 34),
		IntRect(139, 320, 21, 34),
		IntRect(160, 320, 21, 34),
		IntRect(181, 320, 21, 34),
		IntRect(202, 320, 21, 34)
	};

	for (int i = 0; i < 11; i++) {
		font[i].setTexture(texture);
		font[i].setTextureRect(coordinates[i]);
	}

	this->active = active;
	visibleCursor = true;
	text.clear();
	time = 0;
}

void TextBox::setPosition(Vector2f position) {
	boxPos.x = position.x;
	boxPos.y = position.y;
}

bool TextBox::setText(int code) {
	if (code == 13) {
		return true;
	}

	else {
		if (code >= 48 && code <= 57 && text.size() < 3) {
			text.push_back(code - 48);
		}
		if (code == 8 && text.size() != 0) {
			text.pop_back();
		}
	}
	return false;
}

int TextBox::getNumber() {
	int result = 0, count = 1;
	for (int i = text.size() - 1; i >= 0; i--) {
		result += count * text[i];
		count *= 10;
	}
	return result;
}

void TextBox::draw(RenderWindow &window, float time) {
	this->time += time;

	Vector2f cursorPos = boxPos;

	for (auto a : text) {
		font[a].setPosition(cursorPos);
		window.draw(font[a]);
		cursorPos.x += font[a].getTextureRect().width + 6;
	}
	
	if (this->time >= 800) {
		this->time = 0;
		visibleCursor = !visibleCursor;
	}

	if (visibleCursor && active) {
		font[10].setPosition(cursorPos);
		window.draw(font[10]);
	}
}

void TextBox::disable() {
	active = false;
}

void TextBox::activate() {
	active = true;
}

bool TextBox::isActive() {
	return active;
}

void TextBox::clear() {
	text.clear();
}

TextBox::~TextBox() {
}
