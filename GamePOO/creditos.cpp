#include "creditos.h"
#include <SFML/Window/Keyboard.hpp>
#include "menu.h"
#include "nivel.h"
#include <SFML/Graphics/Sprite.hpp>

creditos::creditos() {
	m_t_fondo.loadFromFile("galaxia2.png");
	m_s_fondo.setTexture(m_t_fondo);
	
	m_font.loadFromFile("scifi.ttf");
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	m_t3.setFont(m_font);
	m_t4.setFont(m_font);
	
	m_t1.setString("By @Jeronimo & @Santino");
	m_t1.setPosition(170,150);
	m_t1.setCharacterSize(20);
	
	m_t2.setString("Game Developers");
	m_t2.setPosition(170,200);
	m_t2.setCharacterSize(20);
	
	m_t3.setString("Presione ENTER para continuar (30)");
	m_t3.setPosition(110,350);
	m_t3.setCharacterSize(20);
	m_t2.setFillColor({155,155,155});
	
	m_t4.setString("Presione ESC para volver al menu (30)");
	m_t4.setPosition(100,400);
	m_t4.setCharacterSize(20);
	m_t4.setFillColor({155,155,155});
	
	m_buf.loadFromFile("soundwaiting.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(70);
	
	m_sonido.play();
	
	displayTime = seconds(30);
}

void creditos::update (juego & j) {
	
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	
	m_t1.setFillColor({r,g,b});
	m_t2.setFillColor({r,g,b});
	
	if(Keyboard::isKeyPressed(Keyboard::Key::Return)){
		m_sonido.stop();
		j.setScene(new nivel());
	}
	if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
		m_sonido.stop();
		j.setScene(new menu());
	}
	if(clock.getElapsedTime() >= displayTime){
		m_sonido.stop();
		j.setScene(new menu());
	}
	
	if (enterTimer.getElapsedTime().asSeconds() >= 1) {
		enterTimeLeft--;
		enterTimer.restart();
		if (enterTimeLeft >= 0) {
			m_t3.setString("Presione ENTER para continuar (" + to_string(enterTimeLeft) + ")");
		}
	}
	
	if (escTimer.getElapsedTime().asSeconds() >= 1) {
		escTimeLeft--;
		escTimer.restart();
		if (escTimeLeft >= 0) {
			m_t4.setString("Presione ESC para volver al menu (" + to_string(escTimeLeft) + ")");
		}
	}
}

void creditos::draw (RenderWindow & window) {
	
	window.clear({0,0,0});
	
	window.draw(m_s_fondo);
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	window.draw(m_t4);
	
	window.display();
}

