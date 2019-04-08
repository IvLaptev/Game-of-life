#include "Game.h"

Game::Game() {
	ratio = (float)VideoMode::getFullscreenModes()[0].height/ 1000;
	width = 0;
	height = 0;
}

bool Game::inRect(int x, int y, int key) {
	switch (key) {
	case 0:
		return (x >= 290 && x <= 442 && y >= 240 && y <= 289);
	case 1:
		return (x >= 30 && x <= 430 && y >= 110 && y <= 156);
	case 2:
		return (x >= 35 && x <= 450 && y >= 170 && y <= 210);
	case 3:
		x /= ratio;
		y /= ratio;
		return (x >= 942 && x <= 993 && y >= 7 && y <= 58);
	case 4:
		x /= ratio;
		y /= ratio;
		return (x >= 889 && x <= 940 && y >= 7 && y <= 58);
	case 5:
		x /= ratio;
		y /= ratio;
		return (x >= 241 && x <= 267 && y >= 43 && y <= 67);
	case 6:
		x /= ratio;
		y /= ratio;
		return (x >= 302 && x <= 326 && y >= 43 && y <= 67);
	case 7:
		x /= ratio;
		y /= ratio;
		return (x >= 836 && x <= 887 && y >= 7 && y <= 58);
	}
}

Vector2i Game::findCoordinates(int x, int y) {
	x -= leftBorder;
	x /= cellSize;

	y -= topBorder;
	y /= cellSize;
	return Vector2i(x, y);
}

void Game::addCell(Vector2i coords) {
	if (coords.x >= 0 && coords.x < width && coords.y >= 0 && coords.y < height) {
		cells[{coords.x, coords.y}].setCoordinates(coords);
		cells[{coords.x, coords.y}].changeValue();
		cells[{coords.x, coords.y}].setColor(Color(220, 220, 220));
	}
}

void Game::startWindow() {
	texture.loadFromFile(START_SCREEN);
	form.setTexture(texture);
	form.setTextureRect(IntRect(Vector2i(START_POS), Vector2i(START_SIZE)));

	RectangleShape button;
	button.setSize(Vector2f(162, 59));
	button.setFillColor(Color(255, 230, 200, 50));
	button.setPosition(285, 235);

	Clock clock;
	RenderWindow window(VideoMode(START_SIZE), "Game of life", Style::None);

	TextBox tb1(texture, true);
	TextBox tb2(texture, false);

	tb1.setPosition(Vector2f(230, 116));
	tb2.setPosition(Vector2f(250, 176));

	bool entered = false;
	bool close = false;

	while (window.isOpen())
	{
		bool atEnter = false;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || close)
				window.close();

			if (event.type == Event::TextEntered) {
				if (tb1.isActive()) {
					if (tb1.setText(event.text.unicode)) {
						tb1.disable();
						tb2.activate();
					}
				}
				else {
					if (tb2.isActive()) {
						if (tb2.setText(event.text.unicode)) {
							tb2.disable();
							entered = true;
						}
					}
				}
			}

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					if (inRect(event.mouseButton.x, event.mouseButton.y, ENTER_BUTTON)) {
						entered = true;
					}
					if (inRect(event.mouseButton.x, event.mouseButton.y, TEXT_BOX1)) {
						tb1.activate();
						tb2.disable();
					}
					if (inRect(event.mouseButton.x, event.mouseButton.y, TEXT_BOX2)) {
						tb2.activate();
						tb1.disable();
					}
				}
			}
		}

		if (inRect(Mouse::getPosition(window).x, Mouse::getPosition(window).y, ENTER_BUTTON)) {
			atEnter = true;
		}

		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		window.clear(Color::Black);
		window.draw(form);
		tb1.draw(window, time);
		tb2.draw(window, time);
		if (atEnter) {
			window.draw(button);
		}
		window.display();

		if (entered) {
			width = tb1.getNumber();
			height = tb2.getNumber();
			if (!(width > 0 && width <= 100 && height > 0 && height <= 100)) {
				entered = false;
				tb1.clear();
				tb1.activate();
				
				tb2.clear();
				tb2.disable();

				errorWindow();
			}
			else {
				close = true;
			}
		}
	}
}

void Game::mainWindow() {
	int size = VideoMode::getFullscreenModes()[0].height;
	RenderWindow window(VideoMode(size, size), "Game of life", Style::None);

	texture.loadFromFile(MAIN_SCREEN);
	
	Sprite form;
	form.setTexture(texture);
	form.setScale(ratio, ratio);

	Counter counter(ratio);
	counter.setPosition(Vector2f(273 * ratio, 31 * ratio));

	Texture text;
	createField(text);
	Sprite field;
	field.setTexture(text);
	field.setPosition(leftBorder, topBorder);

	bool close = false;
	bool playing = false;

	Clock clock;
	float time = 0;

	int stepTime = 1700;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || close)
				window.close();

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					if (event.mouseButton.y <= 80 * ratio) {
						if (inRect(event.mouseButton.x, event.mouseButton.y, CLOSE)) {
							close = true;
						}
						if (inRect(event.mouseButton.x, event.mouseButton.y, RESTART)) {
							cells.clear();
							playing = false;
						}
						if (inRect(event.mouseButton.x, event.mouseButton.y, SPEED_UP)) {
							counter.increase();
							if (stepTime > 100) {
								stepTime -= 200;
							}
						}
						if (inRect(event.mouseButton.x, event.mouseButton.y, SPEED_DOWN)) {
							counter.decrease();
							if (stepTime < 1700) {
								stepTime += 200;
							}
						}
						if (inRect(event.mouseButton.x, event.mouseButton.y, START_STOP)) {
							playing = !playing;
							clock.restart();
							time = 0;
						}
					}
					else {
						if (!playing) {
							Vector2i coords = findCoordinates(event.mouseButton.x, event.mouseButton.y);
							addCell(coords);
						}
					}
				}
			}
		}

		if (playing) {
			time += clock.getElapsedTime().asMilliseconds();
			clock.restart();
			if (time > stepTime) {
				time = 0;
				newGeneration();
			}
		}

		window.clear();
		window.draw(form);
		counter.draw(window);
		drawCells(window);
		window.draw(field);
		window.display();
	}
}

void Game::errorWindow() {
	RenderWindow window(VideoMode(ERROR_SIZE), "Game of life: Error", Style::None);

	Texture texture;
	texture.loadFromFile(ERROR_SCREEN);

	Sprite screen;
	screen.setTexture(texture);

	bool close = false;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || close)
				window.close();

			if (event.type == Event::MouseButtonPressed || event.type == Event::KeyPressed) {
				close = true;
			}
		}

		window.clear(Color::Black);
		window.draw(screen);
		window.display();
	}
}

void Game::createField(Texture &text) {
	if (height >= width) {
		int fieldHeight = (1000 - 86) * ratio;
		cellSize = fieldHeight / height;
	}
	else {
		int fieldWidth = (1000 - 12) * ratio;
		cellSize = fieldWidth / width;
	}

	topBorder = 80 * ratio + ((1000 - 86) * ratio - height * cellSize) / 2;
	leftBorder = 6 + ((1000 - 12) * ratio - width * cellSize) / 2;

	RenderTexture field;
	field.create(cellSize*width + 1, cellSize*height + 1);
	field.clear(Color(255, 255, 255));

	RectangleShape line;
	line.setFillColor(Color(150, 150, 150));

	line.setSize(Vector2f(cellSize * width, 1));
	for (int i = 0; i <= height; i++) {
		line.setPosition(Vector2f(0, i * cellSize));
		field.draw(line);
	}
	line.setSize(Vector2f(1, cellSize * height));
	for (int i = 0; i <= width; i++) {
		line.setPosition(Vector2f(i * cellSize, 0));
		field.draw(line);
	}

	field.display();

	Image img = field.getTexture().copyToImage();
	img.createMaskFromColor(Color(255, 255, 255), 0);
	text.loadFromImage(img);
}

void Game::drawCells(RenderWindow &window) {
	for (auto c : cells) {
		if (c.second.isAlive()) {
			RectangleShape cell;
			cell.setFillColor(c.second.getColor());
			cell.setPosition(c.first[0] * cellSize + leftBorder, c.first[1] * cellSize + topBorder);
			cell.setSize(Vector2f(cellSize, cellSize));
			window.draw(cell);
		}
	}
}

void Game::newGeneration() {
	std::map<vector<int>, Cell> nCells;
	Color color(rand() % 255, rand() % 255, rand() % 255);
	for (auto c : cells) {
		if (c.second.isAlive()) {
			Vector2i coords = Vector2i(c.first[0], c.first[1]);
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (!(i == 0 && j == 0)) {
						Vector2i nCoords;
						nCoords.x = (coords.x + i + width) % width;
						nCoords.y = (coords.y + j + height) % height;
						nCells[{nCoords.x, nCoords.y}].addNeighbour();
						nCells[{nCoords.x, nCoords.y}].setCoordinates(nCoords);
					}
				}
			}
		}
	}
	for (auto &c : nCells) {
		if (c.second.getNeighbour() == 3 && !cells[c.first].isAlive()) {
			c.second.setColor(color);
			c.second.changeValue();
		}
		else {
			if ((c.second.getNeighbour() == 3 || c.second.getNeighbour() == 2) && cells[c.first].isAlive()) {
				c.second.setColor(cells[c.first].getColor());
				c.second.changeValue();
			}
		}
	}
	cells = nCells;
}

Game::~Game() {
}
