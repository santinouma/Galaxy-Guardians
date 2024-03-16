#include "fondo.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

fondo::fondo() {
	
	m_t.loadFromFile("galaxia2.png");
	m_s.setTexture(m_t);
	
}

void fondo::draw(RenderWindow &window){
	
	window.draw(m_s);
}
