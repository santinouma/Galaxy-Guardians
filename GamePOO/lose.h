#ifndef LOSE_H
#define LOSE_H
#include "escena.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Sprite.hpp>

class lose : public escena {
public:
	lose();
	void update (juego &j);
	void draw (RenderWindow &window);
private:
	Font m_f;
	Text m_t1, m_t2, m_t3;
	SoundBuffer m_buf;
	Sound m_sonido;
	Sprite m_s_fondo;
	Texture m_t_fondo;
};

#endif

