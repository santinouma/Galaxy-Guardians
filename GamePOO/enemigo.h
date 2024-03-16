#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "disparo.h"
using namespace sf;

class enemigo {
public:            
	enemigo(Texture &textureptr);
	void update();
	void update_2();
	void update_3();
	bool passline();
	void draw_vs(RenderWindow &window);
	void setPosition(float x, float y);
	Vector2f verPosicion();
	float obtenerRadio() const;
	int VerVida();
	void RestarVida();
	bool debeDisparar();
	disparo generarDisparo(Texture &texture);
private:
	Vector2f m_speed_uno = {0, 0.3};
	Vector2f m_speed_dos = {0, 0.2};
	Vector2f m_speed_tres = {0, 0.4};
	Vector2f m_speed_cuatro= {0, 0.3};
	Vector2f m_speed_cinco = {0, 0.5};
	Vector2f m_speed_6 = {0, 0.4};
	bool pasa_la_linea = false;
	Sprite m_s_enemy;
	int m_vida=3;
	Clock m_clock;
};

#endif
