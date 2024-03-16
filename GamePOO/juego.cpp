#include "juego.h"
#include <SFML/Window/VideoMode.hpp>
#include "escena.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "menu.h"
#include <SFML/Window/Event.hpp>
using namespace sf;

juego::juego() : m_w(VideoMode(640,480),"Space Invaders") {
	
	m_w.setFramerateLimit(60);
	
	m_e = new menu();
}

void juego::run() {
	
	while(m_w.isOpen()){
		
		eventos();
		update();
		draw();
		
		if(m_n_e){
			
			delete m_e;
			m_e = m_n_e;
			
			m_n_e = nullptr;
		}
	}
}

void juego::update(){
	
	m_e->update(*this);
}

void juego::eventos(){
	
	Event e;
	
	while(m_w.pollEvent(e)){
		if(e.type == Event::Closed){
			m_w.close();
		}
	}
}

void juego::draw(){
	
	m_e->draw(m_w);
}

void juego::setScene(escena *next_scene){
	
	m_n_e = next_scene;
}
