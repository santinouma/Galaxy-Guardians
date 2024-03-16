#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "escena.h"
using namespace sf;

class escena;

class juego {
public:
	juego();
	void run();
	void update();
	void eventos();
	void draw();
	void setScene(escena *next_scene);
private:
	RenderWindow m_w;
	escena *m_e;
	escena *m_n_e = nullptr;
};

#endif

