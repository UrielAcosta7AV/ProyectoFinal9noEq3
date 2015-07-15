#include "Game.h"

void CGame::InicializandoStage(){
	int n = 0;
	///0
	nivel[n].Nave_BalasMaximas = 1;
	nivel[n].Enemigo_EliminarPorNivel = 1;
	nivel[n].Enemigos_VisiblesAlMismoTiempo=1;
	nivel[n].Enemigo_VelocidadBala = 1;
	nivel[n].Nave_VelocidadBala = 1;
	nivel[n].Enemigo_Velocidad = 2;
	nivel[n++].Nave_Velocidad = 5;
	///1
	nivel[n].Nave_BalasMaximas = 2;
	nivel[n].Enemigo_EliminarPorNivel = 4;
	nivel[n].Enemigos_VisiblesAlMismoTiempo = 2;
	nivel[n].Enemigo_VelocidadBala = 2;
	nivel[n].Nave_VelocidadBala = 2;
	nivel[n].Enemigo_Velocidad = 2;
	nivel[n++].Nave_Velocidad = 1;
	///2
	nivel[n].Nave_BalasMaximas = 4;
	nivel[n].Enemigo_EliminarPorNivel = 10;
	nivel[n].Enemigos_VisiblesAlMismoTiempo = 4;
	nivel[n].Enemigo_VelocidadBala = 10;
	nivel[n].Nave_VelocidadBala = 5;
	nivel[n].Enemigo_Velocidad = 5;
	nivel[n++].Nave_Velocidad = 4;
	///3
	nivel[n].Nave_BalasMaximas = 10;
	nivel[n].Enemigo_EliminarPorNivel = 20;
	nivel[n].Enemigos_VisiblesAlMismoTiempo = 8;
	nivel[n].Enemigo_VelocidadBala = 15;
	nivel[n].Nave_VelocidadBala = 8;
	nivel[n].Enemigo_Velocidad = 6;
	nivel[n++].Nave_Velocidad = 8;
	///4
	nivel[n].Nave_BalasMaximas = 20;
	nivel[n].Enemigo_EliminarPorNivel = 50;
	nivel[n].Enemigos_VisiblesAlMismoTiempo = 15;
	nivel[n].Enemigo_VelocidadBala = 20;
	nivel[n].Nave_VelocidadBala = 20;
	nivel[n].Enemigo_Velocidad = 10;
	nivel[n++].Nave_Velocidad = 18;

}