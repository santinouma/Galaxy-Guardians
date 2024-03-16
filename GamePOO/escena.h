#ifndef ESCENA_H
#define ESCENA_H
#include "juego.h"
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class juego;

class escena {
public:
	escena();
	virtual void update(juego &j) = 0;
	virtual void draw(RenderWindow &window) = 0;
private:
};

#endif
