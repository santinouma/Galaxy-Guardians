#ifndef WIN_H
#define WIN_H
#include "escena.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Sprite.hpp>

class win : public escena {
public:
	win();
	void update (juego &j);
	void draw (RenderWindow &window);
private:
	Font m_f;
	Text m_t1, m_t2, m_t3;
	SoundBuffer m_buf;
	Sound m_sonido;
	Clock clock;
	Time displayTime;
	int enterTimeLeft = 30;
	int escTimeLeft = 30;
	Clock enterTimer;
	Clock escTimer;
	Sprite m_s_fondo;
	Texture m_t_fondo;
};

#endif

