#ifndef MENU_H
#define MENU_H
#include "escena.h"
#include "juego.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

class menu : public escena {
public:
	menu();
	void update(juego &j);
	void draw(RenderWindow &Window);
private:
	Font m_font;
	Text m_t1, m_t2;
	SoundBuffer m_buf;
	Sound m_sonido;
	Sprite m_s_fondo;
	Texture m_t_fondo;
};

#endif


