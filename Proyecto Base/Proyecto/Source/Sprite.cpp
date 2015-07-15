#include "Sprite.h"
#include <stdio.h>
#include <SDL.h>
#include "Nave.h"

Sprite::Sprite(OpenGlImplement *openGlImplement){
	rotate_x = 0.f; 
	rotate_y = 0.f;
	rotate_z = 0.f;
	translate_x = 0.f;
	translate_y = 0.f;
	translate_z = 0.f;
	scale_x = 1.f;
	scale_y = 1.f;
	scale_z = 1.f;
	this->openGlImplement = openGlImplement;
}

Sprite::~Sprite()
{
	delete [] vertexBufferObject;
	delete[] indexBufferObject;
	delete[] textureBufferObject;
	delete[] textureObject;

	delete[] vertexPositions;
	delete[] vertexTextures;
	delete[] vertexIndex;

	delete[] vertexNormals;
}

void Sprite::CreateTextures(char* name){
	SDL_Surface * imagen = SDL_LoadBMP(name);

	if (!imagen)
	{
		printf("No se ha podido cargar la imagen: %s\n", SDL_GetError());
		SDL_Quit();
		exit(3);
	}

	textureObject[0] = openGlImplement->LoadTexture(imagen, vertexPositions[0], vertexPositions[1], vertexPositions[0], vertexPositions[1]);

	SDL_FreeSurface(imagen);
}

	int Sprite::WidthModule(int module){
		return spriteDef.modulos[module].w;
	}

	int Sprite::HeightModule(int module){
		return spriteDef.modulos[module].h;
	}

	Sprite::Sprite(OpenGlImplement* openGlImplement, char * nameResource, int x, int y)
	{
		char pathImg[40];  
		char pathDat[40]; 

		strcpy(pathImg, nameResource);
		strcpy(pathDat, nameResource);
		strcat(pathImg, ".bmp");
		strcat(pathDat, ".dat");

		this->openGlImplement = openGlImplement;

		vertexBufferObject = new GLuint[1];
		indexBufferObject = new GLuint[1];
		textureBufferObject = new GLuint[1];
		textureObject = new GLuint[1];

		Model model = GetOBJinfo(pathDat);
		numero_vertices = model.positions;
		vertexPositions = new GLfloat[model.positions * 3];
		vertexTextures = new GLfloat[model.texels * 2];
		vertexIndex = new GLuint[model.positions];
		vertexNormals = new GLfloat[model.texels * 3];
		
		ExtractOBJdata(pathDat, model.positions);
		CreateTextures(pathImg);

		w = -openGlImplement->ConvertCOORDInvf(vertexPositions[1]);
		h = -openGlImplement->ConvertCOORDInvf(vertexPositions[10]);
		automovimiento = false;
		pasoActual = 0;
		pasoLimite = -1;

		rotate_x = 0.f;
		rotate_y = 0.f;
		rotate_z = 0.f;
		translate_x = x;
		translate_y = y;
		translate_z = 0.f;
		scale_x = 1.f;   //Se cambia tamaño de portada en "x"
		scale_y = 1.f;   //Se cambia tamaño de portada "y"
		scale_z = 400.f; //Se cambia tamaño de portada "z" lo acerca

		faces[model.faces][9];

		openGlImplement->InitBuffers(vertexBufferObject, indexBufferObject, textureBufferObject, vertexPositions, 3 * model.positions * sizeof(vertexPositions), vertexIndex, model.positions * sizeof(GLuint), vertexTextures, 2 * model.texels * sizeof(vertexTextures));
	}

	void Sprite::SetAutoMovimiento(bool automovimiento)
	{
		this->automovimiento = automovimiento;
	}

	void Sprite::Actualizar()
	{
		if (automovimiento)
		{
			MoverLados(1);
			MoverArribaAbajo(1);
		}
		if (pasoLimite>0)
		{
			//pasoActual++;
			if (pasoActual >= pasoLimite)
				pasoActual = 0;
		}
	}

	void Sprite::Draw(){
		openGlImplement->Draw(vertexBufferObject, indexBufferObject, textureBufferObject, textureObject[0], translate_x, translate_y, translate_z, rotate_x,rotate_y,rotate_z,scale_x,scale_y,scale_z, numero_vertices);
	}

	void Sprite::TranslateXYZ(GLfloat x, GLfloat y, GLfloat z){
		translate_x = x;
		translate_y = y;
		translate_z = z;
	}

	void Sprite::TranslateXY(GLfloat x, GLfloat y){
		translate_x = x;
		translate_y = y;
	}

	void Sprite::TranslateZ(GLfloat z){
		translate_z = z;
	}

	void Sprite::TranslateXYDraw(GLfloat x, GLfloat y){
		translate_x = x;
		translate_y = y;
		Draw();
	}

	void Sprite::RotateXYZ(GLfloat x, GLfloat y, GLfloat z){
		rotate_x++;
		rotate_y++;
		rotate_z++;
	}
	void Sprite::ScaleXYZ(GLfloat x, GLfloat y, GLfloat z){
		scale_x = x;
		scale_y = y;
		scale_z = z;
	}

	void Sprite::ScaleXY(GLfloat x, GLfloat y){
		scale_x = x;
		scale_y = y;

	}


	void Sprite::SetVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}

	void Sprite::MoverLados(int posicion){
		translate_x += posicion;
	}

	void Sprite::MoverArribaAbajo(int posicion)
	{
		translate_y += posicion;
	}


	int Sprite::GetX(){
		return translate_x;
	}

	int Sprite::GetY(){
		return translate_y;
	}

	int Sprite::GetW()
	{
		return w;
	}

	int Sprite::GetH()
	{
		return h;
	}

	void Sprite::SetPasoLimite(int pasos)
	{
		this->pasoLimite = pasos;
	}

	int Sprite::ObtenerPasoActual(){
		return pasoActual;
	}

	void Sprite::IncrementarPasoActual()
	{
		pasoActual++;
	}

	Sprite::Model Sprite::GetOBJinfo(std::string fp)
	{
		Model model = { 0 };

		// Open OBJ file
		std::ifstream inOBJ;
		inOBJ.open(fp);
		if (!inOBJ.good())
		{
			exit(1);
		}

		// Read OBJ file
		while (!inOBJ.eof())
		{
			std::string line;
			getline(inOBJ, line);
			std::string type = line.substr(0, 2);

			if (type.compare("v ") == 0)
				model.positions++;
			else if (type.compare("vt") == 0)
				model.texels++;
			else if (type.compare("vn") == 0)
				model.normals++;
			else if (type.compare("f ") == 0)
				model.faces++;
			else if (type.compare("m ") == 0)
				model.modules++;
		}

		model.vertices = model.faces * 3;

		// Close OBJ file
		inOBJ.close();

		return model;
	}

	void Sprite::ExtractOBJdata(std::string fp, GLuint indexes)
	{
		// Counters
		int p = 0;
		int t = 0;
		int n = 0;
		int f = 0;
		int in = 0;
		int m = 0;

		// Open OBJ file
		std::ifstream inOBJ;
		inOBJ.open(fp);
		if (!inOBJ.good())
		{
			exit(1);
		}

		// Read OBJ file
		while (!inOBJ.eof())
		{
			std::string line;
			getline(inOBJ, line);
			std::string type = line.substr(0, 2);

			// Positions
			if (type.compare("v ") == 0)
			{
				// Copy line for parsing
				char* l = new char[line.size() + 1];
				memcpy(l, line.c_str(), line.size() + 1);

				// Extract tokens
				strtok(l, " ");
				for (int i = 0; i < 3; i++)
					vertexPositions[(p * 3) + i] = openGlImplement->ConvertCOORDf(atof(strtok(NULL, " ")));

				// Wrap up
				delete[] l;
				p++;
			}

			// Texels
			else if (type.compare("vt") == 0)
			{
				// Copy line for parsing
				char* l = new char[line.size() + 1];
				memcpy(l, line.c_str(), line.size() + 1);

				// Extract tokens
				strtok(l, " ");
				for (int i = 0; i < 2; i++)
					vertexTextures[(t * 2) + i] = atof(strtok(NULL, " "));
					
				// Wrap up
				delete[] l;
				t++;
			}
			// Index
			else if (type.compare("i ") == 0)
			{
				// Copy line for parsing
				char* l = new char[line.size() + 1];
				memcpy(l, line.c_str(), line.size() + 1);

				// Extract tokens
				strtok(l, " ");
				for (int i = 0; i < indexes; i++)
					vertexIndex[(in * 1) + i] = atoi(strtok(NULL, " "));
				
				// Wrap up
				delete[] l;
				in++;
			}
			// Modules
			else if (type.compare("m ") == 0)
			{
				
			}
			// Normals
			else if (type.compare("vn") == 0)
			{
			}

			// Faces
			else if (type.compare("f ") == 0)
			{
			}
		}

		// Close OBJ file
		inOBJ.close();
	}