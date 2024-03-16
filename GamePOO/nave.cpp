#include "nave.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include "disparo.h"
#include "objeto.h"
using namespace sf;

nave::nave() : objeto("nave_god.png") {
	
	m_s.setScale(0.12,0.12);
	m_s.setPosition(290,405);
	
	m_left = Keyboard::Key::Left;
	m_right = Keyboard::Key::Right;
	m_disp = Keyboard::Key::LShift;
}

void nave::update(){
	
	if(Keyboard::isKeyPressed(m_left)){
		m_s.move(-3.5,0);
	}
	if(Keyboard::isKeyPressed(m_right)){
		m_s.move(3.5,0);
	}
}

bool nave::debeDisparar(){
	
	if(m_clock.getElapsedTime().asMilliseconds()<200)return false;
	if(not Keyboard::isKeyPressed(m_disp)) return false;
	m_clock.restart();
	return true;
}
disparo nave::generarDisparo(Texture &texture){
	Vector2f p = m_s.getPosition();
	Vector2f aux(25.5,-15);
	return disparo(texture,p+aux);
}

int nave::VerVida(){
	return m_vida;
}

void nave::RestarVida(){
	m_vida = m_vida-1;
};
Vector2f nave::verPosicion(){
	return  m_s.getPosition();
}
