#include "disparo.h"
#include <SFML/Graphics.hpp>

disparo::disparo (Texture &texture,Vector2f pos): pos_nave(pos){
	m_s_disp.setTexture(texture);
	m_s_disp.setPosition(pos);
	m_s_disp.setScale(0.27,0.27);
}
void disparo::draw_disp(RenderWindow &w){
	w.draw(m_s_disp);
};
void disparo::update(){
	m_s_disp.move(0,-7);
}
void disparo::update_ovni(){
	m_s_disp.move(0,5);
}
void disparo::update_enemy(){
	m_s_disp.move(0,5);
}
Vector2f disparo::verPosicion(){
	return m_s_disp.getPosition();
}
