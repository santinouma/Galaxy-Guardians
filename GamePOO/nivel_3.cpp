#include "nivel_3.h"
#include "menu.h"
#include "nave.h"
#include <SFML/Graphics/RenderWindow.hpp>
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
#include "nivel_4.h"
#include "escenaIntermedia_3.h"
#include <cstdlib>
#include <ctime> 
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
using namespace std;
using namespace sf;

nivel_3::nivel_3(){
	m_t_fondo.loadFromFile("fondo_nivel4.png");
	m_s_fondo.setTexture(m_t_fondo);
	
	m_tex_disparo.loadFromFile("bala_1.png");
	m_tex_enemy.loadFromFile("enemy_violet.png");
	m_tex_disparo_ovni.loadFromFile("disparo_ovni.png");
	
	m_buf.loadFromFile("soundlevel3.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(50);
	m_sonido.setLoop(true);
	m_sonido.play();
	
	m_disparoSoundBuffer.loadFromFile("navedisparo.ogg");
	m_disparoSound.setBuffer(m_disparoSoundBuffer);
	m_disparoSound.setVolume(20);
	
	ve.emplace_back(m_tex_enemy);
	ve[0].setPosition(100, 50);
	
	ve.emplace_back(m_tex_enemy);
	ve[1].setPosition(200, 75);
	
	ve.emplace_back(m_tex_enemy);
	ve[2].setPosition(300, 95);
	
	ve.emplace_back(m_tex_enemy);
	ve[3].setPosition(400, 115);
	
	ve.emplace_back(m_tex_enemy);
	ve[4].setPosition(310, 135);
	
	ve.emplace_back(m_tex_enemy);
	ve[5].setPosition(150, 155);
	
	ve.emplace_back(m_tex_enemy);
	ve[6].setPosition(250, 180);
	
	ve.emplace_back(m_tex_enemy);
	ve[7].setPosition(350, 205);
	
	ve.emplace_back(m_tex_enemy);
	ve[8].setPosition(450, 140);
	
	ve.emplace_back(m_tex_enemy);
	ve[9].setPosition(440, 100);
	
	ve.emplace_back(m_tex_enemy);
	ve[10].setPosition(189, 155);
	
	ve.emplace_back(m_tex_enemy);
	ve[11].setPosition(250, 210);
	
	ve.emplace_back(m_tex_enemy);
	ve[12].setPosition(50, 205);
	
	ve.emplace_back(m_tex_enemy);
	ve[13].setPosition(450, 140);
	
	ve.emplace_back(m_tex_enemy);
	ve[14].setPosition(270, 130);
	
	
	
	m_ovni = new ovni;
}

void eliminarEnemigo_3(vector<enemigo> &enemys, size_t indice){
	enemys.erase(enemys.begin()+indice);
}
template<typename disparo, typename EnemigoType>
	bool colisiona_3(disparo &d, EnemigoType &e){
	Vector2f pe = e.verPosicion();
	Vector2f pd = d.verPosicion();
	Vector2f v = pd - pe;
	return sqrt(v.x * v.x + v.y * v.y)<30;
}
bool outofscreen_3(disparo &d){			
	Vector2f p = d.verPosicion();
	if(p.x<0 or p.x>640) return true;
	if(p.y<0 or p.y>480)return true;
	return false;
}
	int randomNumber(int min, int max) {
		return min + rand() % ((max + 1) - min);
	}
void nivel_3::update(juego &j){
	m_n.update();
	if (m_n.debeDisparar()) {
		m_disparoSound.play();
		vd.push_back(m_n.generarDisparo(m_tex_disparo));
	}
	if(m_ovni!=nullptr && m_ovni->debeDisparar()){
		vd_ovni.push_back(m_ovni->generarDisparo(m_tex_disparo_ovni));
	}
	srand(time(NULL));
	for (size_t i = 0; i < ve.size(); ++i) {
		// Suponiendo que 'debeDisparar' sea una función que retorna true si el enemigo debe disparar
		if (ve[i].debeDisparar()) {
			// Generar un número aleatorio entre 1 y 100
			int randomChance = randomNumber(1, 100);
			
			// Si el número aleatorio es menor o igual al 20 (20% de probabilidad), el enemigo dispara
			if (randomChance <= 15) {
				vd_enemy.push_back(ve[i].generarDisparo(m_tex_disparo));
			}
		}
	}
	for (disparo &d : vd) {
		d.update();
		if (outofscreen_3(d)) {
			auto it = remove_if(vd.begin(), vd.end(), outofscreen_3);
			cout << "se elimino disparo fuera de pantalla " << endl;
			vd.erase(it, vd.end());
		}
	}
	for(disparo &d:vd_ovni){
		d.update_ovni();
		if (outofscreen_3(d)) {
			auto it = remove_if(vd_ovni.begin(), vd_ovni.end(), outofscreen_3);
			cout << "se elimino disparo fuera de pantalla " << endl;
			vd_ovni.erase(it, vd_ovni.end());
		}
	}
	for(disparo &d:vd_enemy){
		d.update_enemy();
		if (outofscreen_3(d)) {
			auto it = remove_if(vd_enemy.begin(), vd_enemy.end(), outofscreen_3);
			cout << "se elimino disparo fuera de pantalla " << endl;
			vd_enemy.erase(it, vd_enemy.end());
		}
	}
	vector<size_t> disparos_a_eliminar;
	vector<size_t> enemigos_a_eliminar;
	vector<size_t> disparos_ovni_a_eliminar;
	vector<size_t> disparos_enemy_a_eliminar;
	for (size_t i = 0; i < vd.size(); ++i) {
		for (size_t j = 0; j < ve.size(); ++j) {
			if (colisiona_3(vd[i], ve[j])) {
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
		if(m_ovni != nullptr && colisiona_3(vd[i], *m_ovni)) {
			disparos_a_eliminar.push_back(i);
			m_ovni->RestarVida();
			if(m_ovni->VerVida() == 0){
				delete m_ovni;
				m_ovni = nullptr;
			}
		}
	}
	for(size_t i=0;i<vd_ovni.size();++i){
		if(colisiona_3(vd_ovni[i],m_n)){
			disparos_ovni_a_eliminar.push_back(i);
			m_n.RestarVida();
			if(m_n.VerVida()==0){
				m_sonido.stop();
				j.setScene(new lose());
			}
		}
	}
	for(size_t i=0;i<vd_enemy.size();++i){
		if(colisiona_3(vd_enemy[i],m_n)){
			disparos_enemy_a_eliminar.push_back(i);
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
	for (auto it = disparos_enemy_a_eliminar.rbegin(); it != disparos_enemy_a_eliminar.rend(); ++it) {
		vd_enemy.erase(vd_enemy.begin() + *it);
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
		eliminarEnemigo_3(ve, *it);
	}
	if(ve.empty() && m_ovni == nullptr) {
		m_sonido.stop();
		j.setScene(new escenaIntermedia_3());
	}

	m_n.update();
	
	for (enemigo &d : ve) {
		d.update_3();
	}

	if (m_ovni != nullptr) {
		m_ovni->update();
	}
}
void nivel_3::draw(RenderWindow &window){

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
	for(disparo &d:vd_enemy){
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
nivel_3::~nivel_3(){
	if(m_ovni != nullptr){
		delete m_ovni;
		m_ovni = nullptr;
	}
}				

