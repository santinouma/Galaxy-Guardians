#ifndef FONDO_H
#define FONDO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

class fondo {
public:
	fondo();
	void draw(RenderWindow &window);
private:
	Texture m_t;
	Sprite m_s;
};

#endif

