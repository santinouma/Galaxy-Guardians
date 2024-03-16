#include "menu.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "juego.h"
#include "nivel.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "escenaIntro.h"
#include "controles.h"
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

menu::menu() {
	m_t_fondo.loadFromFile("galaxia2.png");
	m_s_fondo.setTexture(m_t_fondo);
	
	m_font.loadFromFile("scifi.ttf");
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	
	m_t1.setString("Galaxy Guardians");
	m_t1.setPosition(70,150);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("Presione ENTER para continuar");
	m_t2.setPosition(140,350);
	m_t2.setCharacterSize(20);
	m_t2.setFillColor({200,200,200});
	
	m_buf.loadFromFile("soundmenu.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(50);
	
	m_sonido.setLoop(true);
	
	m_sonido.play();
}

void menu::update(juego &j) {
	
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	
	m_t1.setFillColor({r,g,b});
	
	if(Keyboard::isKeyPressed(Keyboard::Key::Return)){
		m_sonido.stop();
		j.setScene(new controles());
	}
}

void menu::draw(RenderWindow &window) {
	
	window.clear({0,0,0});
	
	window.draw(m_s_fondo);
	window.draw(m_t1);
	window.draw(m_t2);
	
	window.display();
}

