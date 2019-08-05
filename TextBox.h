#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

/***********************************
 ласс, представл€ющий текстовое поле
***********************************/

class TextBox {
	vector<int> text;	// введЄнное значение
	Sprite font[11];	// шрифт и курсор
	Vector2f boxPos;	// местоположение
	float time;
	bool active;		// заполн€етс€ ли сейчас
	bool visibleCursor;	// видимый курсор
public:
	TextBox(Texture&, bool);	// инициализаци€ переменных

	void setPosition(Vector2f);	// установка координат на поле

	bool setText(int);	// ввод символа в поле

	int getNumber();	// вывод значени€ пол€ в виде числа

	void draw(RenderWindow&, float);	// вывод пол€ на экран

	void disable();		// сделать не активным

	void activate();	// сделать активным

	bool isActive();	// проверить активность

	void clear();		// очистить текстовое значение
	
	~TextBox();
};

#endif