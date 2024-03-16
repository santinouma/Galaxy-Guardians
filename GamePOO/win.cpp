#include "win.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "nivel.h"
#include "menu.h"
#include "creditos.h"
#include <SFML/Graphics/Sprite.hpp>

win::win() {
	m_t_fondo.loadFromFile("fondo_win.png");
	m_s_fondo.setTexture(m_t_fondo);
	m_s_fondo.setScale(1,1.8);
	
	m_f.loadFromFile("scifi.ttf");
	m_t1.setFont(m_f);
	m_t2.setFont(m_f);
	m_t3.setFont(m_f);
	
	m_t1.setString("You Won!");
	m_t1.setPosition(180,150);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("!La galaxia esta libre!...por ahora");
	m_t2.setPosition(130,300);
	m_t2.setCharacterSize(20);
	m_t2.setFillColor({0,255,51});
	
	m_t3.setString("Creditos en...(30)");
	m_t3.setPosition(225,400);
	m_t3.setCharacterSize(20);
	m_t3.setFillColor({255,0,51});
	
	m_buf.loadFromFile("soundwin.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(50);
	
	m_sonido.play();
	
	displayTime = seconds(30);
}

void win::update(juego &j){
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	
	m_t1.setFillColor({r,g,b});
	
	if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
		m_sonido.stop();
		j.setScene(new menu());
	}
	if(clock.getElapsedTime() >= displayTime){
		m_sonido.stop();
		j.setScene(new creditos());
	}
	
	if (enterTimer.getElapsedTime().asSeconds() >= 1) {
		enterTimeLeft--;
		enterTimer.restart();
		if (enterTimeLeft >= 0) {
			m_t3.setString("Creditos en...(" + to_string(enterTimeLeft) + ")");
		}
	}
}

void win::draw (RenderWindow & window) {
	window.clear({0,0,0});
	
	window.draw(m_s_fondo);
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	
	window.display();
}
