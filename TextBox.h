#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class TextBox {
	vector<int> text;
	Sprite font[11];
	Vector2f boxPos;
	float time;
	bool active;
	bool visibleCursor;
public:
	TextBox(Texture&, bool);

	void setPosition(Vector2f);

	bool setText(int);

	int getNumber();

	void draw(RenderWindow&, float);

	void disable();

	void activate();

	bool isActive();

	void clear();
	
	~TextBox();
};

#endif