#ifndef FINALBOSS_H
#define FINALBOSS_H
#include "objeto.h"
#include "disparo.h"

class FinalBoss : public objeto {
public:
	FinalBoss();
	void update();
	void RestarVida();
	int VerVida();
	float obtenerRadio() const;
	Vector2f verPosicion();
	bool debeDisparar();
	disparo generarDisparo(Texture &texture);
private:
	Vector2f m_speed = {9,0};
	int m_vida = 10;
};

#endif

