#include "enemigo.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

enemigo::enemigo(Texture &textureptr) {
	m_s_enemy.setTexture(textureptr);
	m_s_enemy.setScale(0.07, 0.07);
}

void enemigo::update() {
	m_s_enemy.move(m_speed_uno); // Mueve cada enemigo en la primera fila
	
	// Mueve cada enemigo en las filas restantes
	if (m_s_enemy.getPosition().y > 100) {
		m_s_enemy.move(m_speed_dos);
	}
}
void enemigo::update_2() {
	m_s_enemy.move(m_speed_tres); // Mueve cada enemigo en la primera fila
	
	// Mueve cada enemigo en las filas restantes
	if (m_s_enemy.getPosition().y > 100) {
		m_s_enemy.move(m_speed_cuatro);
	}
}
void enemigo::update_3() {
	m_s_enemy.move(m_speed_dos); // Mueve cada enemigo en la primera fila
	
	// Mueve cada enemigo en las filas restantes
	if (m_s_enemy.getPosition().y > 100) {
		m_s_enemy.move(m_speed_tres);
	}
}

bool enemigo::passline(){ //podria ser metodo de enemigo simplemente pero da igual, como quieras, puede considerarse como cualquiera de los dos (si pinta cambialo)
	for(int i=0;i<10;++i){
		auto p = this->m_s_enemy.getPosition();
		if(p.y+28 > 395){ //35 aprox. es lo que mide el bicho, 420 es donde se situa la nave
			pasa_la_linea = true;
			break;
		}
	}
	return pasa_la_linea;
}

void enemigo::RestarVida(){
	m_vida = m_vida-1;
}

Vector2f enemigo::verPosicion(){
	return  m_s_enemy.getPosition();
}

void enemigo::draw_vs(RenderWindow &window) {
	window.draw(m_s_enemy); // Dibuja el sprite de enemigo en su posición actual
}

void enemigo::setPosition(float x, float y) {
	m_s_enemy.setPosition(x, y);
}

int enemigo::VerVida(){
	return m_vida;
}

bool enemigo::debeDisparar(){
	if(m_clock.getElapsedTime().asMilliseconds()<600)return false;
	m_clock.restart();
	return true;
}
disparo enemigo::generarDisparo(Texture &texture){
	Vector2f p = m_s_enemy.getPosition();
	Vector2f aux(p.x + m_s_enemy.getGlobalBounds().width / 2, p.y + m_s_enemy.getGlobalBounds().height);
	return disparo(texture, aux);
}
//float enemigo::obtenerRadio() const {
//FloatRect bounds =m_s_enemy.getGlobalBounds();
//float radio = (bounds.width + bounds.height) / 4.0f;
//return radio;
//}
