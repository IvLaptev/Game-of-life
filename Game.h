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

class Game {
	Texture texture;
	Sprite form;
	std::map<vector<int>, Cell> cells;
	float ratio;
	int height;
	int width;
	int topBorder;
	int leftBorder;
	int cellSize;
public:
	Game();

	bool inRect(int x, int y, int key);

	Vector2i findCoordinates(int x, int y);

	void addCell(Vector2i);

	void startWindow();

	void mainWindow();

	void errorWindow();

	void createField(Texture &);

	void drawCells(RenderWindow &);

	void newGeneration();

	~Game();
};

#endif