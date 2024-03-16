#include "controles.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "escenaIntro.h"

controles::controles() {
	m_t_fondo.loadFromFile("galaxia2.png");
	m_s_fondo.setTexture(m_t_fondo);
	
	m_font.loadFromFile("scifi.ttf");
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	m_t3.setFont(m_font);
	
	m_t1.setString("CONTROLS");
	m_t1.setPosition(150,150);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("MOVIMIENTO: <---  --->");
	m_t2.setPosition(180,350);
	m_t2.setCharacterSize(20);
	m_t2.setFillColor({0,102,255});
	
	m_t3.setString("DISPARO: LShift");
	m_t3.setPosition(220,400);
	m_t3.setCharacterSize(20);
	m_t3.setFillColor({255,51,51});
	
	m_buf.loadFromFile("soundwaiting.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(70);
	
	m_sonido.setLoop(true);
	
	m_sonido.play();
	
	displayTime = seconds(7);
}

void controles::update (juego & j) {
	
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	
	m_t1.setFillColor({r,g,b});
	
	if (clock.getElapsedTime() >= displayTime) {
		m_sonido.stop();
		j.setScene(new escenaIntro());
	}
}

void controles::draw (RenderWindow & window) {
	
	window.clear({0,0,0});
	
	window.draw(m_s_fondo);
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	
	window.display();
	
}

