#ifndef COUNTER_H_
#define COUNTER_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "codes.h"
using namespace sf;

/**********************************
 ласс, представл€ющий собой счЄтчик
**********************************/

class Counter
{
	Texture texture;	// текстура шрифта
	Sprite font[9];		// спрайты шрифта
	int count;		// значение счЄтчика
	double ratio;		// коэффициент масштабировани€
public:
	Counter(double ratio);	// конструктор, инициализирующий стартовые значени€

	void setPosition(Vector2f position);	// установка координат

	void increase();	// увеличение на единицу

	void decrease();	// уменьшение на единицу

	void draw(RenderWindow &);	// изображение на экране

	~Counter();
};

#endif