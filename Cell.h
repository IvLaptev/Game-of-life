#ifndef CELL_H_
#define CELL_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "codes.h"
using namespace sf;

class Cell {
	Color color;
	Vector2i coords;
	int neighbours;
	bool alive;
public:

	Cell();

	bool isAlive();

	void changeValue();

	void addNeighbour();

	int getNeighbour();

	void setCoordinates(Vector2i &);

	void setColor(Color color);

	Color getColor();

	Cell operator= (const Cell& c);

	~Cell();
};

#endif