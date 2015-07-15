#include "SpriteDeF.h"
#include "Config.h"

SpriteDef::SpriteDef(){
	modulos[0].id = 0;
	modulos[0].x = 0;
	modulos[0].y = 0;
	modulos[0].w = 64;
	modulos[0].h = 64;

	modulos[1].id = 1;
	modulos[1].x = 0;
	modulos[1].y = 0;
	modulos[1].w = WIDTH_SCREEN;
	modulos[1].h = HEIGHT_SCREEN;

	modulos[2].id = 2;
	modulos[2].x = 0;
	modulos[2].y = 0;
	modulos[2].w = 54;
	modulos[2].h = 61;

	//titulo
	modulos[3].id = 3;
	modulos[3].x = 0;
	modulos[3].y = 29;
	modulos[3].w = 542;
	modulos[3].h = 67;

	//Nombre
	modulos[4].id = 4;
	modulos[4].x = 159;
	modulos[4].y = 231;
	modulos[4].w = 177;
	modulos[4].h = 25;

	//Iniciar1
	modulos[5].id = 5;
	modulos[5].x = 59;
	modulos[5].y = 145;
	modulos[5].w = 102;
	modulos[5].h = 24;

	//Salir1
	modulos[6].id = 6;
	modulos[6].x = 62;
	modulos[6].y = 168;
	modulos[6].w = 82;
	modulos[6].h = 22;

	//Iniciar2
	modulos[7].id = 7;
	modulos[7].x = 305;
	modulos[7].y = 142;
	modulos[7].w = 95;
	modulos[7].h = 23;

	//Salir2
	modulos[8].id = 8;
	modulos[8].x = 308;
	modulos[8].y = 165;
	modulos[8].w = 85;
	modulos[8].h = 24;

	modulos[9].id = 9;
	modulos[9].x = 0;
	modulos[9].y = 0;
	modulos[9].w = 5;
	modulos[9].h = 5;
}