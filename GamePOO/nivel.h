#ifndef NIVEL_H
#define NIVEL_H
#include "escena.h"
#include "nave.h"
#include "enemigo.h"
#include "ovni.h"
#include "fondo.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "disparo.h"
#include <vector>

using namespace std;

class nivel : public escena {
public:
	nivel();
	void update(juego &j);
	void draw(RenderWindow &window);
	~nivel();
private:
	void generar_enemigos();
	
	nave m_n;
	//enemigo m_enemy1, m_enemy2;//son 2 enemigos y una navecita que es como la que los spawnea, enemigo m_enemy1,2 y nave, vector podria ser una solucion si queremos hacer varios, o bien un map que seria facil encontrar cada cosa
	ovni *m_ovni;
	vector<disparo> vd;
	Texture m_tex_disparo;
	vector<disparo> vd_ovni;
	Texture m_tex_disparo_ovni;
	vector<enemigo> ve;
	Texture m_tex_enemy;
	//demas objetos m_o;
	
	SoundBuffer m_buf, m_disparoSoundBuffer;
	Sound m_sonido, m_disparoSound;
	
	Sprite m_s_fondo;
	Texture m_t_fondo;
};

#endif
