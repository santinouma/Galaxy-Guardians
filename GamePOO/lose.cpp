#include "lose.h"
#include <SFML/Window/Keyboard.hpp>
#include "nivel.h"
#include "menu.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

lose::lose() {
	m_t_fondo.loadFromFile("fondo_lose.png");
	m_s_fondo.setTexture(m_t_fondo);
	m_s_fondo.setScale(1,1.2);
	
	m_f.loadFromFile("scifi.ttf");
	m_t1.setFont(m_f);
	m_t2.setFont(m_f);
	m_t3.setFont(m_f);
	
	m_t1.setString("You Lose!");
	m_t1.setPosition(180,150);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("Presione ENTER para reintentar");
	m_t2.setPosition(135,350);
	m_t2.setCharacterSize(20);
	m_t2.setFillColor({200,200,200});
	
	m_t3.setString("Presione ESC para volver al menu");
	m_t3.setPosition(125,400);
	m_t3.setCharacterSize(20);
	m_t3.setFillColor({200,200,200});
	
	m_buf.loadFromFile("soundlose.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(50);
	
	m_sonido.play();
}

void lose::update (juego &j) {
	
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	
	m_t1.setFillColor({r,g,b});
	
	if(Keyboard::isKeyPressed(Keyboard::Key::Return)){
		m_sonido.stop();
		j.setScene(new nivel());
	}
	if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
		m_sonido.stop();
		j.setScene(new menu());
	}
}

void lose::draw (RenderWindow &window) {
	
	window.clear({0,0,0});
	
	window.draw(m_s_fondo);
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	
	window.display();
}

