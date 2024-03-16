#ifndef DISPARO_H
#define DISPARO_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class disparo{
public:
	disparo(Texture &texture,Vector2f pos);
	void update();
	void update_ovni();
	void update_enemy();
	void draw_disp(RenderWindow &w);
	Vector2f verPosicion();
private:
	Sprite m_s_disp;
	Vector2f pos_nave;
};
#endif


