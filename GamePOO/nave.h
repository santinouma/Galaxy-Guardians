#ifndef NAVE_H
#define NAVE_H
#include <SFML/Window/Keyboard.hpp>
#include "disparo.h"
#include "objeto.h"
using namespace sf;

class disparo;

class nave : public objeto{
public:
	nave();
	void update();
	bool debeDisparar();
	disparo generarDisparo(Texture &texture);
	Vector2f verPosicion();
	void RestarVida();
	int VerVida();
	//void DibujarVida(RenderWindow &w);
private:
	Keyboard::Key m_right, m_left, m_disp;
	int m_vida=3;
};

#endif

