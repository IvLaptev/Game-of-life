#ifndef COUNTER_H_
#define COUNTER_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "codes.h"
using namespace sf;

class Counter
{
	Texture texture;
	Sprite font[9];
	int count;
	double ratio;
public:
	Counter(double ratio);

	void setPosition(Vector2f position);

	void increase();

	void decrease();

	void draw(RenderWindow &);

	~Counter();
};

#endif