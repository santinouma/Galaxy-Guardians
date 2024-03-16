#include "FinalBoss.h"

FinalBoss::FinalBoss() : objeto("boss_2.png"){
	
	m_s.setScale(0.35,0.35);
	m_s.setPosition(250,5);
	
}

void FinalBoss::update(){
	
	m_s.move(m_speed);
	
	auto p = m_s.getPosition();
	
	if(p.x < 0 or p.x+85 > 640){
		m_speed.x = -m_speed.x;
	}
}

void FinalBoss::RestarVida(){
	m_vida = m_vida-1;
}

int FinalBoss::VerVida(){
	return m_vida;
}

//float ovni::obtenerRadio() const {
//FloatRect bounds = m_s.getGlobalBounds();
//float radio = (bounds.width + bounds.height) / 4.0f;
//return radio;
//}

Vector2f FinalBoss::verPosicion(){
	return m_s.getPosition();
}
bool FinalBoss::debeDisparar(){
	if(m_clock.getElapsedTime().asMilliseconds()<900)return false;
	m_clock.restart();
	return true;
}
disparo FinalBoss::generarDisparo(Texture &texture){
	Vector2f p = m_s.getPosition();
	Vector2f aux(p.x + m_s.getGlobalBounds().width / 2, p.y + m_s.getGlobalBounds().height);
	return disparo(texture, aux);
}
