#include "menu.h"
#include "nave.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "nivel.h"
#include "enemigo.h"
#include "lose.h"
#include "ovni.h"
#include "fondo.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "win.h"
#include <iostream>
#include <memory>
#include "nivel_2.h"
#include "escenaIntermedia.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace std;
using namespace sf;

nivel::nivel(){
	m_t_fondo.loadFromFile("fondo_nivel2.png");
	m_s_fondo.setTexture(m_t_fondo);
	
	m_tex_disparo.loadFromFile("bala_1.png");
	m_tex_enemy.loadFromFile("invader1.png");
	m_tex_disparo_ovni.loadFromFile("disparo_ovni.png");
	
	m_buf.loadFromFile("soundlevel1.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(50);
	m_sonido.setLoop(true);
	m_sonido.play();
	
	m_disparoSoundBuffer.loadFromFile("navedisparo.ogg");
	m_disparoSound.setBuffer(m_disparoSoundBuffer);
	m_disparoSound.setVolume(20);
	
	ve.emplace_back(m_tex_enemy);
	ve[0].setPosition(60, 60);
	
	ve.emplace_back(m_tex_enemy);
	ve[1].setPosition(160, 110);
	
	ve.emplace_back(m_tex_enemy);
	ve[2].setPosition(260, 160);
	
	ve.emplace_back(m_tex_enemy);
	ve[3].setPosition(360, 210);
	
	ve.emplace_back(m_tex_enemy);
	ve[4].setPosition(460, 260);
	
	ve.emplace_back(m_tex_enemy);
	ve[5].setPosition(110, 310);
	
	ve.emplace_back(m_tex_enemy);
	ve[6].setPosition(210, 235);
	
	ve.emplace_back(m_tex_enemy);
	ve[7].setPosition(310, 180);
	
	ve.emplace_back(m_tex_enemy);
	ve[8].setPosition(410, 150);
	
	ve.emplace_back(m_tex_enemy);
	ve[9].setPosition(510, 110);
	
	m_ovni = new ovni;
}

void eliminarEnemigo_1(vector<enemigo> &enemys, size_t indice){
	enemys.erase(enemys.begin()+indice);
}
	template<typename disparo, typename EnemigoType>
		bool colisiona_1(disparo &d, EnemigoType &e){
		Vector2f pe = e.verPosicion();
		Vector2f pd = d.verPosicion();
		Vector2f v = pd - pe;
		return sqrt(v.x * v.x + v.y * v.y)<30;
	}
		bool outofscreen_1(disparo &d){
			Vector2f p = d.verPosicion();
			if(p.x<0 or p.x>640) return true;
			if(p.y<0 or p.y>480)return true;
			return false;
		}
			void nivel::update(juego &j){
				m_n.update();
				
				if (m_n.debeDisparar()) {
					m_disparoSound.play();
					vd.push_back(m_n.generarDisparo(m_tex_disparo));
				}
				if(m_ovni!=nullptr && m_ovni->debeDisparar()){
					vd_ovni.push_back(m_ovni->generarDisparo(m_tex_disparo_ovni));
				}
				for (disparo &d : vd) {
					d.update();
					if (outofscreen_1(d)) {
						auto it = remove_if(vd.begin(), vd.end(), outofscreen_1);
						cout << "se elimino disparo fuera de pantalla " << endl;
						vd.erase(it, vd.end());
					}
				}
				for(disparo &d:vd_ovni){
					d.update_ovni();
					if (outofscreen_1(d)) {
						auto it = remove_if(vd_ovni.begin(), vd_ovni.end(), outofscreen_1);
						cout << "se elimino disparo fuera de pantalla " << endl;
						vd_ovni.erase(it, vd_ovni.end());
					}
				}
				vector<size_t> disparos_a_eliminar;
				vector<size_t> enemigos_a_eliminar;
				vector<size_t> disparos_ovni_a_eliminar;
				
				for (size_t i = 0; i < vd.size(); ++i) {
					for (size_t j = 0; j < ve.size(); ++j) {
						if (colisiona_1(vd[i], ve[j])) {
							disparos_a_eliminar.push_back(i);
							cout<<"Colisiono y se elimino disparo"<<endl;
							ve[j].RestarVida();
							if (ve[j].VerVida() == 0) {
								enemigos_a_eliminar.push_back(j);
							}
						}
					}
				}
				for (size_t i = 0; i < vd.size(); ++i) {
					if(m_ovni != nullptr && colisiona_1(vd[i], *m_ovni)) {
						disparos_a_eliminar.push_back(i);
						m_ovni->RestarVida();
						
						if(m_ovni->VerVida() == 0){
							delete m_ovni;
							m_ovni = nullptr;
						}
					}
				}
				for(size_t i=0;i<vd_ovni.size();++i){
					if(colisiona_1(vd_ovni[i],m_n)){
						disparos_ovni_a_eliminar.push_back(i);
						m_n.RestarVida();
						if(m_n.VerVida()==0){
							m_sonido.stop();
							j.setScene(new lose());
						}
					}
				}
				for(auto it = disparos_a_eliminar.rbegin(); it != disparos_a_eliminar.rend(); ++it) {
					vd.erase(vd.begin() + *it);
				}
				for (auto it = disparos_ovni_a_eliminar.rbegin(); it != disparos_ovni_a_eliminar.rend(); ++it) {
					vd_ovni.erase(vd_ovni.begin() + *it);
				}
				if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
					m_sonido.stop();
					j.setScene(new menu());
				}
				for (size_t i = 0; i < ve.size(); ++i) {
					if (ve[i].passline()) {
						enemigos_a_eliminar.push_back(i);
						m_n.RestarVida();
						if(m_n.VerVida()==0){
							m_sonido.stop();
							j.setScene(new lose());
						}
					}
				}
				for(auto it = enemigos_a_eliminar.begin(); it != enemigos_a_eliminar.end(); ++it) {
					eliminarEnemigo_1(ve, *it);
				}
				if(ve.empty() && m_ovni == nullptr) {
					m_sonido.stop();
					j.setScene(new escenaIntermedia());
				}
				
				m_n.update();
				
				for (enemigo &d : ve) {
					d.update();
				}
				
				if (m_ovni != nullptr) {
					m_ovni->update();
				}
			}
			
			void nivel::draw(RenderWindow &window){
				
				window.clear({0,0,0});
				
				window.draw(m_s_fondo);
				
				Vector2f vidaSize(20, 20);
				Vector2f vidaOffset(10, window.getSize().y - vidaSize.y - 10);
				Color vidaColor(0, 255, 0);
				
				for (int i = 0; i < m_n.VerVida(); ++i) {
					RectangleShape vidaRect(vidaSize);
					vidaRect.setFillColor(vidaColor);
					vidaRect.setPosition(vidaOffset.x + i * (vidaSize.x + 5), vidaOffset.y);
					window.draw(vidaRect);
				}
				
				Font font;
				font.loadFromFile("scifi.ttf");
				Vector2f healthOffset = Vector2f(10, window.getSize().y - 40);
				
				Text healthText;
				healthText.setFont(font);
				healthText.setString("Health");
				healthText.setCharacterSize(16); 
				healthText.setFillColor(Color::White); 
				healthText.setPosition(healthOffset.x, healthOffset.y - 20); 
				
				window.draw(healthText);
				
				m_n.draw(window);
				
				for(disparo &d:vd){
					d.draw_disp(window);
				}
				for(disparo &d:vd_ovni){
					d.draw_disp(window);
				}
				if(m_ovni!=nullptr){
					m_ovni->draw(window);
				}
				
				for(auto &e:ve){
					e.draw_vs(window);
				}
				
				window.display();
			}
			
			nivel::~nivel(){
				if(m_ovni != nullptr){
					delete m_ovni;
					m_ovni = nullptr;
				}
			}
