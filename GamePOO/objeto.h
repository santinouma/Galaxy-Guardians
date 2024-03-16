#ifndef OBJETO_H
#define OBJETO_H
#include "escena.h"
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
using namespace std;
using namespace sf;

class objeto{
public:
	objeto(const string name);
	objeto(Texture* textureptr);
	void draw(RenderWindow &window);
protected:
	Texture m_t;
	Sprite m_s;
	Clock m_clock;
};

#endif

