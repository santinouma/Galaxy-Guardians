#ifndef CREDITOS_H
#define CREDITOS_H
#include "escena.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace std;

class creditos : public escena {
public:
	creditos();
	void update (juego & j);
	void draw (RenderWindow & window);
private:
	Font m_font;
	Text m_t1, m_t2, m_t3, m_t4;
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

