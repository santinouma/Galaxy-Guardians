#ifndef OVNI_H
#define OVNI_H
#include "objeto.h"
#include "disparo.h"

class ovni : public objeto {
public:
	ovni();
	void update();
	void RestarVida();
	int VerVida();
	float obtenerRadio() const;
	Vector2f verPosicion();
	bool debeDisparar();
	disparo generarDisparo(Texture &texture);
private:
	Vector2f m_speed = {9,0};
	int m_vida = 2;
};

#endif

