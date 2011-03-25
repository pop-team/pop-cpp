#include "screen.ph"
#include "fractal.ph"
#include "tile.h"
#include "chrono.h"

/* display window */
#define DISP_WIDTH 900
#define DISP_HEIGHT 900
#define DISP_N 4

/* origin and scale for x and y axis */
#define REAL_MIN -2.
#define REAL_MAX .6
#define IMAG_MIN -1.3
#define IMAG_MAX 1.3

#define nbMaxMachines 200
#define MachinesList "machines.ip"


Screen::Screen()
{
	// nothing
}
Screen::~Screen()
{
	// nothing
}


static Chronometer *chronosp;


int Screen::run(int argc, char cmdline[32][32])
{
	if (argc!=7)
	{
		printf("Usage: parocrun obj.map ./parocrun num-careaux real-min real-max imag-min imag-max nbWorkers\n\n");
		return -1;
	}
	chronosp = new Chronometer(1000);
	chronosp->lap("start screen");
	int w, h, dispn = DISP_N, a = 1, ind, i, j;
	float	rma = REAL_MAX, rmi = REAL_MIN,
								ima = IMAG_MAX, imi = IMAG_MIN,
													  rs, is;

	paroc_string* machine[nbMaxMachines];
	FILE *f;
	int nbOfMachines  = 0;
	int  nbWorker;


	char *argv[argc];
	for (i=0; i<argc; i++) {
		argv[i] = cmdline[i];
	}
	argv[i] = 0;

	initApp(argc, argv);

	dispn = atoi(argv[a++]);
	if (argc > 4) {
		rmi = atof(argv[a++]);
		rma = atof(argv[a++]);
		imi = atof(argv[a++]);
		ima = atof(argv[a++]);
	}

	// Get the available machines
	int nbWorkers=atoi(argv[a++]);
	if ( (f = fopen(MachinesList, "r"))!=NULL)
	{
		char* s;
		s=(char*)malloc(100);
		while (fscanf(f, "%s", s)!=EOF)
		{
			machine[nbOfMachines] = new paroc_string(s);
			nbOfMachines++;
		}
		fclose(f);
	}
	else
		for (nbOfMachines=0; nbOfMachines<nbWorker; nbOfMachines++)
			machine[nbOfMachines] = new paroc_string("localhost");

	printf("Available machines:\n");
	for (int i=0; i<nbOfMachines; i++)
		printf("  %d = %s \n", i, (const char*)(*machine[i]));

	initFrame(DISP_WIDTH, DISP_HEIGHT, dispn);
	w = DISP_WIDTH/dispn;
	h = DISP_HEIGHT/dispn;
	rs = (rma-rmi)/DISP_WIDTH;
	is = (ima-imi)/DISP_HEIGHT;

	tile = new Tile* [dispn*dispn];
	Fractal ** ft= new Fractal*[DISP_N*DISP_N];//added lwk

	chronosp->lap("start tile loop");
	for (i=dispn-1; i>=0; i--) {
		for (j=0; j<dispn; j++) {
			ind = i * dispn + j;
			tile[ind] = new Tile(i*w, j*h, w, h);
		}
	}
	chronosp->lap("end tile loop");

	Screen myself(this);

	int shift = 0;//rand() % nbOfMachines;

	chronosp->lap("start call loop");
	for (i=dispn-1; i>=0; i--) {
		for (j=0; j<dispn; j++) {
			ind = i * dispn + j;
			printf("Run a new fractal object (ind=%d, x=%d, y=%d) on %s\n",ind,i,j,(const char *)*(machine[(ind+shift)%nbWorkers]));
			//lwk Fractal *f = new Fractal();
			ft[ind] = new Fractal(*(machine[(ind+shift)%nbWorkers]));
			//else
			//	ft[ind] = new Fractal("localhost");
			//lwk f->generate(w, h, rmi + rs*i*w, rs,
			//	imi + is*j*h, is, ind, myself);
			ft[ind]->generate(w, h, rmi + rs*i*w, rs,
							  imi + is*j*h, is, ind, myself);
			//printf("Init fractal object finished (ind=%d)\n",ind);

		}
	}
	chronosp->lap("end call loop");


	int r = appExec();

	//added lwk
	for (i=0;i<dispn*dispn;i++)delete ft[i];
	delete ft;

	chronosp->dump("log_chrono");
	return r;
}


void Screen::newRow(int ind, int row, int s, int *v)
{
	tile[ind]->newRow(row, (unsigned int *) v);
}


void Screen::endTile(int ind)
{
	chronosp->lap("end tile %d", ind);
}

//lwk
@pack(Screen);
