#include "objeto.h"
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

objeto::objeto(const string name) {
	m_t.loadFromFile(name);
	m_s.setTexture(m_t);
}

objeto::objeto(Texture* textureptr) {
	if (textureptr == nullptr) {
		cout << "Error: Puntero a la textura es nulo." << endl;
	} else {
		m_s.setTexture(*textureptr);
	}
}

void objeto::draw(RenderWindow &window) {
	window.draw(m_s);
}
