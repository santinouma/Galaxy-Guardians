#include "nivel_4.h"
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
#include <cstdlib>
#include <ctime> 
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
using namespace std;
using namespace sf;

nivel_4::nivel_4(){
	m_t_fondo.loadFromFile("fondo_nivel3.png");
	m_s_fondo.setTexture(m_t_fondo);
	
	m_tex_disparo.loadFromFile("bala_1.png");
	m_tex_enemy.loadFromFile("enemy_extranbotico.png");
	m_tex_disparo_boss.loadFromFile("disparo_ovni.png");
	
	m_buf.loadFromFile("soundlevel4.ogg");
	m_sonido.setBuffer(m_buf);
	m_sonido.setVolume(50);
	m_sonido.setLoop(true);
	m_sonido.play();
	
	m_disparoSoundBuffer.loadFromFile("navedisparo.ogg");
	m_disparoSound.setBuffer(m_disparoSoundBuffer);
	m_disparoSound.setVolume(20);
	
	ve.emplace_back(m_tex_enemy);
	ve[0].setPosition(100, 100);
	
	ve.emplace_back(m_tex_enemy);
	ve[1].setPosition(200, 150);
	
	ve.emplace_back(m_tex_enemy);
	ve[2].setPosition(300, 200);
	
	ve.emplace_back(m_tex_enemy);
	ve[3].setPosition(400, 250);
	
	ve.emplace_back(m_tex_enemy);
	ve[4].setPosition(310, 300);
	
	ve.emplace_back(m_tex_enemy);
	ve[5].setPosition(150, 220);
	
	ve.emplace_back(m_tex_enemy);
	ve[6].setPosition(250, 230);
	
	ve.emplace_back(m_tex_enemy);
	ve[7].setPosition(350, 255);
	
	ve.emplace_back(m_tex_enemy);
	ve[8].setPosition(450, 190);
	
	ve.emplace_back(m_tex_enemy);
	ve[9].setPosition(440, 150);
	
	m_boss = new FinalBoss;
}

void eliminarEnemigo_4(vector<enemigo> &enemys, size_t indice){
	enemys.erase(enemys.begin()+indice);
}
template<typename disparo, typename EnemigoType>
	bool colisiona_4(disparo &d, EnemigoType &e){
	Vector2f pe = e.verPosicion();
	Vector2f pd = d.verPosicion();
	Vector2f v = pd - pe;
	return sqrt(v.x * v.x + v.y * v.y)<30;
}
bool outofscreen_4(disparo &d){			
	Vector2f p = d.verPosicion();
	if(p.x<0 or p.x>640) return true;
	if(p.y<0 or p.y>480)return true;
	return false;
}
	int randomNumber_2(int min, int max) {
		return min + rand() % ((max + 1) - min);
	}
void nivel_4::update(juego &j){
	m_n.update();
	if (m_n.debeDisparar()) {
		m_disparoSound.play();
		vd.push_back(m_n.generarDisparo(m_tex_disparo));
	}
	if(m_boss!=nullptr && m_boss->debeDisparar()){
		vd_boss.push_back(m_boss->generarDisparo(m_tex_disparo_boss));
	}
	srand(time(NULL));
	for (size_t i = 0; i < ve.size(); ++i) {
		// Suponiendo que 'debeDisparar' sea una función que retorna true si el enemigo debe disparar
		if (ve[i].debeDisparar()) {
			// Generar un número aleatorio entre 1 y 100
			int randomChance = randomNumber_2(1, 100);
			
			// Si el número aleatorio es menor o igual al 20 (20% de probabilidad), el enemigo dispara
			if (randomChance <= 20) {
				vd_enemy.push_back(ve[i].generarDisparo(m_tex_disparo));
			}
		}
	}
	for (disparo &d : vd) {
		d.update();
		if (outofscreen_4(d)) {
			auto it = remove_if(vd.begin(), vd.end(), outofscreen_4);
			cout << "se elimino disparo fuera de pantalla " << endl;
			vd.erase(it, vd.end());
		}
	}
	for(disparo &d:vd_boss){
		d.update_ovni();
		if (outofscreen_4(d)) {
			auto it = remove_if(vd_boss.begin(), vd_boss.end(), outofscreen_4);
			cout << "se elimino disparo fuera de pantalla " << endl;
			vd_boss.erase(it, vd_boss.end());
		}
	}
	for(disparo &d:vd_enemy){
		d.update_enemy();
		if (outofscreen_4(d)) {
			auto it = remove_if(vd_enemy.begin(), vd_enemy.end(), outofscreen_4);
			cout << "se elimino disparo fuera de pantalla " << endl;
			vd_enemy.erase(it, vd_enemy.end());
		}
	}
	
	vector<size_t> disparos_a_eliminar;
	vector<size_t> enemigos_a_eliminar;
	vector<size_t> disparos_boss_a_eliminar;
	vector<size_t> disparos_enemy_a_eliminar;
	for (size_t i = 0; i < vd.size(); ++i) {
		for (size_t j = 0; j < ve.size(); ++j) {
			if (colisiona_4(vd[i], ve[j])) {
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
		if (m_boss != nullptr && colisiona_4(vd[i], *m_boss)) {
			disparos_a_eliminar.push_back(i);
			m_boss->RestarVida();
			if (m_boss->VerVida() == 0) {
				delete m_boss;
				m_boss = nullptr;
			} else {
				actualizarVidasJefe(window); // Actualizar las vidas del jefe gráficamente
			}
		}
	}
	for(size_t i=0;i<vd_boss.size();++i){
		if(colisiona_4(vd_boss[i],m_n)){
			disparos_boss_a_eliminar.push_back(i);
			m_n.RestarVida();
			if(m_n.VerVida()==0){
				m_sonido.stop();
				j.setScene(new lose());
			}
		}
	}
	for(size_t i=0;i<vd_enemy.size();++i){
		if(colisiona_4(vd_enemy[i],m_n)){
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
	for (auto it = disparos_boss_a_eliminar.rbegin(); it != disparos_boss_a_eliminar.rend(); ++it) {
		vd_boss.erase(vd_boss.begin() + *it);
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
		eliminarEnemigo_4(ve, *it);
	}
	if(ve.empty() && m_boss == nullptr) {
		m_sonido.stop();
		j.setScene(new win());
	}

	m_n.update();
	
	for (enemigo &d : ve) {
		d.update();
	}
	
	if (m_boss != nullptr) {
		m_boss->update();
	}
}
void nivel_4::draw(RenderWindow &window){
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
	
	if (m_boss != nullptr) {
		Vector2f bossVidaSize(40, 10); // Reducir el tamaño en altura y aumentar en anchura
		Vector2f bossVidaOffset(10, 10); // Posición inicial para las vidas del jefe
		Color bossVidaColor(255, 0, 0); // Color rojo para las vidas del jefe
		
		// Calcular el espacio disponible para distribuir las vidas del jefe
		float availableWidth = window.getSize().x - 2 * bossVidaOffset.x;
		float vidaSpacing = availableWidth / 10; // Dividir el espacio en 10 partes para las 10 vidas del jefe
		
		for (int i = 0; i < m_boss->VerVida(); ++i) { // El jefe tiene 10 vidas
			RectangleShape bossVidaRect(bossVidaSize);
			bossVidaRect.setFillColor(bossVidaColor);
			bossVidaRect.setPosition(bossVidaOffset.x + i * vidaSpacing, bossVidaOffset.y);
			window.draw(bossVidaRect);
		}
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
	for(disparo &d:vd_boss){
		d.draw_disp(window);
	}
	for(disparo &d:vd_enemy){
		d.draw_disp(window);
	}
	if(m_boss!=nullptr){
		m_boss->draw(window);
	}

	for(auto &e:ve){
		e.draw_vs(window);
	}

	window.display();
}

void nivel_4::actualizarVidasJefe(RenderWindow &window) {
	if (m_boss != nullptr) {
		Vector2f bossVidaSize(40, 10); // Tamaño inicial de la vida del jefe
		Vector2f bossVidaOffset(10, 10); // Posición inicial para las vidas del jefe
		Color bossVidaColor(255, 0, 0); // Color rojo para las vidas del jefe
		
		// Calcular el tamaño de las vidas del jefe según la cantidad actual de vidas
		float vidaPorcentaje = (float)m_boss->VerVida() / 10;
		bossVidaSize.x *= vidaPorcentaje; // Reducir el tamaño en proporción a las vidas restantes
		
		// Calcular el espacio disponible para distribuir las vidas del jefe
		float availableWidth = window.getSize().x - 2 * bossVidaOffset.x;
		float vidaSpacing = availableWidth / 10; // Dividir el espacio en partes para las vidas del jefe
		
		// Dibujar las vidas del jefe actualizadas
		for (int i = 0; i < m_boss->VerVida(); ++i) {
			RectangleShape bossVidaRect(bossVidaSize);
			bossVidaRect.setFillColor(bossVidaColor);
			bossVidaRect.setPosition(bossVidaOffset.x + i * vidaSpacing, bossVidaOffset.y);
			window.draw(bossVidaRect);
		}
	}
}

	nivel_4::~nivel_4(){
		if(m_boss != nullptr){
		delete m_boss;
		m_boss = nullptr;
	}
}
