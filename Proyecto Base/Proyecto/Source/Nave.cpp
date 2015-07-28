#include "Nave.h"
#include "Config.h"
#include <stdlib.h>

Nave::~Nave(){
	delete nave;
	for (int i = 0; i < MAXIMO_DE_BALAS; i++)
		delete bala[i];

}

Nave::Nave(OpenGlImplement* openGlImplement, char*rutaImagen, int x, int y, int tipoNave)
{
	nave = new Sprite(openGlImplement, rutaImagen, x, y);
	for (int i = 0; i < MAXIMO_DE_BALAS; i++)
	{
		switch (tipoNave)
		{
		case NAVE_PROPIA:
		bala[i] = new Sprite(openGlImplement, "Balas", 0, 0);
		bala[i]->SetVisible(false);
			break;

		case NAVE_ENEMIGA:
			bala[i] = new Sprite(openGlImplement, "BalasE", 0, 0);
			bala[i]->SetVisible(false);
			break;
		}

			
	
		

	
	}

	balaVisible = 0;
	visible = true;
	colision = false;
	this->tipoNave = tipoNave;
}

void Nave::crearNuevo(int pos)
{
	balaVisible = 0;
	visible = true;
	colision = false;
	for (int i = 0; i < MAXIMO_DE_BALAS; i++)
	{
		bala[i]->SetVisible(false);
	}
	if (tipoNave == NAVE_PROPIA)
		nave->TranslateXY(pos, HEIGHT_SCREEN - 64);
	if (tipoNave == NAVE_ENEMIGA)
		nave->TranslateXY(pos, 0);
}

void Nave::Disparar(int balas)
{
	if (visible)
	{
		bala[balaVisible]->SetVisible(true);
		switch (tipoNave)
		{
		case NAVE_PROPIA:

			bala[balaVisible]->TranslateXY(nave->GetX() + nave->GetW() / 2, nave->GetY());
			break;

		case NAVE_ENEMIGA:
			bala[balaVisible]->TranslateXY(nave->GetX() + nave->GetW() / 2, nave->GetY() + nave->GetH());

			break;
		}
		balaVisible++;

		if (balaVisible >= balas)
			balaVisible = 0;
	}
}

void Nave::Draw()
{
	
	if (visible){
		
		//
		//nave->translate_x(10);
		
		nave->Draw();
		for (int i = 0; i < MAXIMO_DE_BALAS; i++)
		{
			
			bala[i]->Draw();
			bala[i]->ScaleXYZ(5.f, 5.f, 5.f);
			switch (tipoNave)
			{
			case NAVE_PROPIA:
				nave->ScaleXYZ(10.f, 10.f, 10.f);
				//nave->rotate_x = -10;
				nave->RotateXYZ(5.f, 5.f, 5.f);
				
				//nave->rotate_z = 100;
				

				bala[i]->MoverArribaAbajo(-10);
				
			
				break;

			case NAVE_ENEMIGA:
				nave->ScaleXYZ(15.f, 15.f, 15.f);
				nave->rotate_z = 180;
				//nave->rotate_y = 20;
				bala[i]->MoverArribaAbajo(10);
			
				break;
			}
		}
	}
}

void Nave::MoverAbajo(int velocidad)
{
	nave->MoverArribaAbajo(velocidad);
}
void Nave::MoverArriba(int velocidad)
{
	nave->MoverArribaAbajo(-velocidad);
}
void Nave::MoverDerecha(int velocidad)
{
	nave->MoverLados(velocidad);
}
void Nave::MoverIzquierda(int velocidad)
{
	nave->MoverLados(-velocidad);
}
Sprite*Nave::GetNaveObjeto()
{
	return nave;
}

void Nave::AutoDisparar(int balas)
{
	if ((rand()%100)<2)
	{
		Disparar(balas);
	}
}

void Nave::setVisible(bool visible)
{
	
	this->visible = visible;
}

void Nave::TranslateXYZ(GLfloat x, GLfloat y, GLfloat z){
	translate_x = x;
	translate_y = y;
	translate_z = z;
}

void Nave::TranslateXY(GLfloat x, GLfloat y){
	translate_x = x;
	translate_y = y;
}

void Nave::TranslateZ(GLfloat z){
	translate_z = z;
}

void Nave::TranslateXYDraw(GLfloat x, GLfloat y){
	translate_x = x;
	translate_y = y;
	Draw();
}

void Nave::RotateXYZ(GLfloat x, GLfloat y, GLfloat z){
	rotate_x++;
	rotate_y++;
	rotate_z++;
}

//void Nave::ScaleXYZ(GLfloat x, GLfloat y, GLfloat z){
//	scale_x = x;
//	scale_y = y;
//	scale_z = z;
//}
//void Nave::ScaleX(GLfloat x){
//	scale_x = x;
//
//}

bool Nave::Colision(Nave * nave, TipoColision tipoColision){
	int x_o, y_o, w_o, h_o;
	int x, y, w, h;
	
	switch (tipoColision){

		x = GetNaveObjeto()->GetX();
		y = GetNaveObjeto()->GetY();
		w = GetNaveObjeto()->GetW();
		h = GetNaveObjeto()->GetH();
		
		x_o = nave->GetNaveObjeto()->GetX();
		y_o = nave->GetNaveObjeto()->GetY();
		w_o = nave->GetNaveObjeto()->GetW();
		h_o = nave->GetNaveObjeto()->GetH();

		if ((x <= x_o + w_o && 	y <= y_o + h_o) && (x_o <= x + w && y_o <= y + h))
			return true;

		break;
	case TipoColision::BALA:
		x = nave->GetNaveObjeto()->GetX();
		y = nave->GetNaveObjeto()->GetY();
		w = nave->GetNaveObjeto()->GetW();
		h = nave->GetNaveObjeto()->GetH();

		for (int i = 0; i < MAXIMO_DE_BALAS; i++){
			x_o = bala[i]->GetX();
			y_o = bala[i]->GetY();
			w_o = bala[i]->GetW();
			h_o = bala[i]->GetH();

			if ((x <= x_o + w_o && 	y <= y_o + h_o) && (x_o <= x + w && y_o <= y + h))
				return true;
		}
		break;
	}

	return false;

}