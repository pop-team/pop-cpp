#ifndef TILE_H
#define TILE_H

class Tile {
private:
	int x, y, w, h;
	void *widget;
public:
	Tile(int ax, int ay, int aw, int ah);
	void newRow(int row, unsigned int *v);
};

void initApp(int &argc, char **argv);
void initFrame(int dw, int dh, int dispn);
int appExec();

#endif
