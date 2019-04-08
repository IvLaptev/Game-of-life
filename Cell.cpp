#include "Cell.h"

Cell::Cell() {
	alive = false;
	neighbours = 0;
}

bool Cell::isAlive() {
	return alive;
}

void Cell::changeValue() {
	alive = !alive;
}

void Cell::addNeighbour() {
	neighbours++;
}

int Cell::getNeighbour() {
	return neighbours;
}

void Cell::setCoordinates(Vector2i &coordinates) {
	coords = coordinates;
}

void Cell::setColor(Color color) {
	this->color = color;
}

Color Cell::getColor() {
	return color;
}

Cell Cell::operator= (const Cell& c) {
	this->alive = c.alive;
	this->coords = c.coords;
	this->neighbours = c.neighbours;
	return *this;
}


Cell::~Cell() {
}
