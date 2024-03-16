#include "escenaIntro.h"
#include "nivel_2.h"
#include <SFML/Graphics/Font.hpp>
#include "nivel.h"
#include <SFML/Graphics/Sprite.hpp>

escenaIntro::escenaIntro() {
	m_t_fondo.loadFromFile("fondo_pantallasdecarga.png");
	m_s_fondo.setTexture(m_t_fondo);
	
	m_font.loadFromFile("scifi.ttf");
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	m_t3.setFont(m_font);
	
	m_t1.setString("GET READY");
	m_t1.setPosition(150,150);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("!Preparate para la batalla Galactica!");
	m_t2.setPosition(115,350);
	m_t2.setCharacterSize(20);
	m_t2.setFillColor({0,102,255});
	
	m_t3.setString("Esquiva y dispara, !NOS INVADEN!");
	m_t3.setPosition(125,400);
	m_t3.setCharacterSize(20);
	m_t3.setFillColor({255,51,51});
	
	m_buf.loadFromFile("soundwaiting.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(70);
	
	m_sonido.setLoop(true);
	
	m_sonido.play();
	
	displayTime = seconds(5);
}

void escenaIntro::update (juego & j) {
	
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	
	m_t1.setFillColor({r,g,b});
	
	if (clock.getElapsedTime() >= displayTime) {
		m_sonido.stop();
		j.setScene(new nivel());
	}
	
}

void escenaIntro::draw (RenderWindow & window) {
	
	window.clear({0,0,0});
	
	window.draw(m_s_fondo);
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	
	window.display();
}


