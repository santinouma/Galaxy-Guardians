#include "escenaIntermedia_2.h"
#include "nivel_3.h"
#include "escenaIntermedia.h"

escenaIntermedia_2::escenaIntermedia_2() {
	m_t_fondo.loadFromFile("fondo_pantallasdecarga.png");
	m_s_fondo.setTexture(m_t_fondo);
	
	m_font.loadFromFile("scifi.ttf");
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	m_t3.setFont(m_font);
	
	m_t1.setString("Ready for Nvl 3");
	m_t1.setPosition(80,150);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("Las TrotaMundos evolucionaron a los extranboticos");
	m_t2.setPosition(35,350);
	m_t2.setCharacterSize(18);
	m_t2.setFillColor({153,0,204});
	
	m_t3.setString("!SON MAS RAPIDOS Y FUERTES!");
	m_t3.setPosition(135,400);
	m_t3.setCharacterSize(20);
	m_t3.setFillColor({255,51,51});
	
	
	m_buf.loadFromFile("soundwaiting.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(70);
	
	m_sonido.setLoop(true);
	
	m_sonido.play();
	
	displayTime = seconds(5);
}

void escenaIntermedia_2::update(juego &j) {
	
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	
	m_t1.setFillColor({r,g,b});
	
	if (clock.getElapsedTime() >= displayTime) {
		m_sonido.stop();
		j.setScene(new nivel_3());
	}
	
}

void escenaIntermedia_2::draw(RenderWindow &window) {
	
	window.clear({0,0,0});
	
	window.draw(m_s_fondo);
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	
	window.display();
}

