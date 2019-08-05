#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "TextBox.h"
#include "Counter.h"
#include "Cell.h"
#include "codes.h"
using namespace sf;

/***********************
 ласс, управл€ющий игрой
***********************/

class Game {
	Texture texture;	// текстура окна
	Sprite form;		// спрайт окна
	std::map<vector<int>, Cell> cells;	// клеткак и еЄ координаты
	float ratio;		// коэффициент масштабировани€
	int height;		// высота пол€ в клетках
	int width;		// ширина пол€ в клетках
	int topBorder;		// верхний отступ пол€
	int leftBorder;		// нажний отступ пол€
	int cellSize;		// размер €чейки
public:
	Game();	// конструктор, считающий ratio

	bool inRect(int x, int y, int key);	// провер€ет на нажатие на элемент интерфейса

	Vector2i findCoordinates(int x, int y);	// переводит координаты окна в координаты пол€

	void addCell(Vector2i);	// добавл€ет €чейку в список

	void startWindow();	// создаЄт стартовое окно

	void mainWindow();	// создаЄт главное окно

	void errorWindow();	// создаЄт окно ошибки ввода

	void createField(Texture &);	// создаЄт игровое поле и заносит его в текстуру

	void drawCells(RenderWindow &);	// рисует клетки

	void newGeneration();	// считает новое поколение

	~Game();
};

#endif