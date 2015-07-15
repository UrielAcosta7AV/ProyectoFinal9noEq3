#ifndef __NAVE_H__
#define __NAVE_H__
#include "Sprite.h"
#include "Config.h"
#include "SDL_opengl.h"

class Nave
{
	Sprite * nave;
	Sprite * bala[MAXIMO_DE_BALAS];
	int balaVisible;
	bool visible;
	bool colision;
	int tipoNave;
public:
	enum TipoColision{
		NAVE,
		BALA,
	};

	Nave(OpenGlImplement* openGlImplement, char*rutaImagen, int x, int y, int tipoNave);
	~Nave();
	void Draw();
	void Disparar(int balas);
	void AutoDisparar(int balas);
	void MoverArriba(int velocidad);
	void MoverAbajo(int velocidad);
	void MoverIzquierda(int velocidad);
	void MoverDerecha(int velocidad);
	Sprite* GetNaveObjeto();
	void setVisible(bool visible);
	bool Colision(Nave * nave, TipoColision tipoColision);
	void crearNuevo(int pos);
	//////////// OPENGL
	GLuint GetTexture();

	///////////////////

	void TranslateXYZ(GLfloat x, GLfloat y, GLfloat z);
	void TranslateXY(GLfloat x, GLfloat y);
	void TranslateZ(GLfloat z);
	void TranslateXYDraw(GLfloat x, GLfloat y);
	void RotateXYZ(GLfloat x, GLfloat y, GLfloat z);
	//void ScaleXYZ(GLfloat x, GLfloat y, GLfloat z);
	//void ScaleX(GLfloat x);
	//void ScaleXY(GLfloat x, GLfloat y);

	GLfloat rotate_x;
	GLfloat rotate_y;
	GLfloat rotate_z;
	GLfloat translate_x;
	GLfloat translate_y;
	GLfloat translate_z;
	GLfloat scale_x;
	GLfloat scale_y;
	GLfloat scale_z;
};
#endif