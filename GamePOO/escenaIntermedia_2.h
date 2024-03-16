#ifndef ESCENAINTERMEDIA_2_H
#define ESCENAINTERMEDIA_2_H
#include "escena.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Sprite.hpp>

class escenaIntermedia_2 : public escena {
public:
	escenaIntermedia_2();
	void update(juego &j);
	void draw(RenderWindow &window);
private:
	Font m_font;
	Text m_t1, m_t2, m_t3;
	SoundBuffer m_buf;
	Sound m_sonido;
	Clock clock;
	Time displayTime;
	Sprite m_s_fondo;
	Texture m_t_fondo;
};

#endif

