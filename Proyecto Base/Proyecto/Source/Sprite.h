#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <SDL.h>
#include "SpriteDeF.h"
#include "OpegGLImplement.h"
#include "Config.h"
#include "SDL_opengl.h"

class Sprite{
	int w;
	int h;

	int pasos;
	int pasoActual;
	int pasoLimite;
	bool isVisible;
	bool automovimiento;
	
	SpriteDef spriteDef;//definiciones de sprite

public:
	Sprite(OpenGlImplement *openGlImplement);//constructor recibe la pantalla
	~Sprite();
	void CreateTextures (char * name);
	
	int WidthModule(int module);
	int HeightModule(int module);

	void SetVisible(bool isVisible);
	void MoverArribaAbajo(int posicion);

	Sprite(OpenGlImplement* openGlImplement, char * nameResource, int x, int y);

	void SetAutoMovimiento(bool automovimiento);
	void SetPasoLimite(int pasos);
	int ObtenerPasoActual();
	void IncrementarPasoActual();
	//bool EstaColicionando(Objeto * b);
	void Draw();
	
	void TranslateXYZ(GLfloat x, GLfloat y, GLfloat z);
	void TranslateXY(GLfloat x, GLfloat y);
	void TranslateZ(GLfloat z);
	void TranslateXYDraw(GLfloat x, GLfloat y);
	void RotateXYZ(GLfloat x, GLfloat y, GLfloat z);
	void ScaleXYZ(GLfloat x, GLfloat y, GLfloat z);
	void ScaleXY(GLfloat x, GLfloat y);
	

	GLfloat rotate_x;
	GLfloat rotate_y;
	GLfloat rotate_z;
	GLfloat translate_x;
	GLfloat translate_y;
	GLfloat translate_z;
	GLfloat scale_x;
	GLfloat scale_y;
	GLfloat scale_z;

	GLuint numero_vertices;

	void MoverLados(int posicion);
	void Actualizar();
	int GetY();
	int GetX();
	int GetW();
	int GetH();

	/////////// OPENGL
	// Model Structure
	typedef struct Model
	{
		int vertices;
		int positions;
		int texels;
		int normals;
		int faces;
		int modules;
	}
	Model;

	Model GetOBJinfo(std::string fp);
	void ExtractOBJdata(std::string fp, GLuint indexs);

	OpenGlImplement *openGlImplement;

	GLuint* vertexBufferObject;
	GLuint* indexBufferObject;
	GLuint* textureBufferObject;
	GLuint* textureObject;

	GLfloat* vertexPositions; 
	GLfloat* vertexTextures; 
	GLuint* vertexIndex;

	GLfloat* vertexNormals;  
	GLuint faces[][9];              // PTN PTN PTN

	//////////////////
};


#endif