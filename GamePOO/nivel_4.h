#ifndef NIVEL_4_H
#define NIVEL_4_H
#include "escena.h"
#include "nave.h"
#include "enemigo.h"
#include "fondo.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "disparo.h"
#include <vector>
#include "FinalBoss.h"

using namespace sf;
using namespace std;

class nivel_4 : public escena {
public:
	nivel_4();
	void update(juego &j);
	void draw(RenderWindow &window);
	void actualizarVidasJefe(RenderWindow &window);
	~nivel_4();
private:
	void generar_enemigos();
	
	RenderWindow window;
	
	nave m_n;
	//enemigo m_enemy1, m_enemy2;//son 2 enemigos y una navecita que es como la que los spawnea, enemigo m_enemy1,2 y nave, vector podria ser una solucion si queremos hacer varios, o bien un map que seria facil encontrar cada cosa
	FinalBoss *m_boss;
	vector<disparo> vd;
	Texture m_tex_disparo;
	vector<disparo> vd_boss;
	Texture m_tex_disparo_boss;
	vector<enemigo> ve;
	Texture m_tex_enemy;
	vector<disparo> vd_enemy;
	//demas objetos m_o;
	
	SoundBuffer m_buf, m_disparoSoundBuffer;
	Sound m_sonido, m_disparoSound;
	
	Sprite m_s_fondo;
	Texture m_t_fondo;
};


#endif


