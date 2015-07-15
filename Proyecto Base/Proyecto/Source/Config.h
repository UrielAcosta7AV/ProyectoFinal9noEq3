#ifndef _CONFIG_H_
#define _CONFIG_H_

#define GL_GLEXT_PROTOTYPES
#define VERSION "0.0.6"

#define WIDTH_SCREEN 640
#define HEIGHT_SCREEN 640

#define BORDE_IZQUIERDO 1<<0
#define BORDE_SUPERIOR  1<<1
#define BORDE_DERECHO   1<<2
#define BORDE_INFERIOR  1<<3

#define FPS_LIMIT 30.0f
#define FPS_DELAY 1000.0f / FPS_LIMIT

#define MENU_OPCION1	0
#define MENU_OPCION2	MENU_OPCION1+1


#define MAXIMO_DE_BALAS 30
#define MAXIMO_DE_NIVELES 5
#define MAXIMO_DE_ENEMIGOS 15

#define NAVE_PROPIA 0
#define NAVE_ENEMIGA 1

#define CERO 0
#define UNO 1


#endif