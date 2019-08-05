#ifndef CELL_H_
#define CELL_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "codes.h"
using namespace sf;

/*****************************
 ласс обозначающий €чейку пол€
*****************************/

class Cell {
	Color color;		// цвет €чейки
	Vector2i coords;	// координаты €чейки на поле
	int neighbours;		// кол-во соседей
	bool alive;		// признак того, что клетка жива
public:

	Cell();		// базовый конструктор

	bool isAlive();	// узнаЄт, жива ли клетка

	void changeValue();	// мен€ет alive на противоположенное

	void addNeighbour();	// добавл€ет одного сосед к соотв. переменной

	int getNeighbour();	// возвращает кол-во соседей

	void setCoordinates(Vector2i &);	// устанавливает координаты клетки на поле

	void setColor(Color color);	// устанавливает цвет клетки

	Color getColor();	// возвращает цвет клетки

	Cell operator= (const Cell& c);

	~Cell();
};

#endif