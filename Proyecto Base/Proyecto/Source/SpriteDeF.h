#ifndef _SPRITEDEF_H_
#define _SPRITEDEF_H_

class SpriteDef
{
	public:
	struct Modulos
	{
		int id;
		int x;
		int y;
		int w;
		int h;
	};

	Modulos modulos [9];//<--- # de modulos
	SpriteDef();
};

#endif				