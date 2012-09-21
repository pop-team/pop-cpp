#ifndef SCREEN_H
#define SCREEN_H

#ifndef FRACTAL_H
#include "tile.h"
#endif

parclass Screen
{
	classuid(1001);
public:
	//Screen();
	Screen() @{od.url("localhost");};//added lwk
	~Screen();
	sync conc int run([in] int argc, [in] char argv[32][32]);
	async conc void newRow([in] int tilen,
			[in] int row, [in] int s, [in, size=s] int *v);
	async conc void endTile([in] int tilen);

private:
#ifndef FRACTAL_H
	Tile **tile;
#endif
};

#endif
