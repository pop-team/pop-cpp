#include "fractal.ph"
#include "screen.ph"

#include <math.h>

#define MAX_SQLEN 4.0
/* Maximum number of iterations */
#define MAX_ITER	18


#define frac_next()	({\
          temp = zreal * zreal - zimag * zimag + creal;\
          zimag = (2. * zreal * zimag + cimag);\
          zreal = temp;\
          sqlength = zreal * zreal + zimag * zimag;\
          count ++;\
})


#define BCOL(a)		((uint)((a)*255)&0xff)
#define RGB(r, g, b)	(BCOL(r)<<16|BCOL(g)<<8|BCOL(b))
#define LOG2 0.301029996

#ifdef BFIN

/* To increase computation speed on the blackfin board, we use integer instead of float for calculations */
static uint color(float creal, float cimag)
{
	const int M=900; // M should be larger (or equal) than the size of one tile, but not too big either
	int creal_i=creal*M;
	int cimag_i=cimag*M;
	int temp, zreal = 0, zimag = 0;
	int sqlength=1;

	//complex_fract16 z={0,0},zconj={0,0};
	float h, s, v, m, n, f;
	int i;
	uint count = 0;

	do {
		/*frac_next();*/
		temp = (zreal * zreal - zimag * zimag)/M + creal_i;
		zimag = (2 * zreal * zimag)/M + cimag_i;
		zreal = temp;
		sqlength = zreal * zreal + zimag * zimag;
		count++;
	}
	while ((sqlength< MAX_SQLEN*M*M) && (count < MAX_ITER));

	sqlength/=M*M;

	//frac_next();
	//frac_next();

	if (count == MAX_ITER)
		return RGB(0,0,0);

	//return RGB(1,1,1); // If we stop here, no color is added

	h = count - log(log(sqrt(sqlength))) / LOG2;

	/* h is given on [0, 6] or UNDEFINED.
	* s and v are given on [0, 1].
	*/
	s = v = 1.;
	h -= (((int)(h / 6)) * 6);

	i = (int) h;
	f = h - i;

	if (!(i & 1))
		f = 1. - f;
	m = v * (1. - s);
	n = v * (1. - s * f);
	switch (i%6) {
	case 0: return RGB(v, n, m);
	case 1: return RGB(n, v, m);
	case 2: return RGB(m, v, n);
	case 3: return RGB(m, n, v);
	case 4: return RGB(n, m, v);
	case 5: return RGB(v, m, n);
	}
	return RGB(0,0,0);
}
#else
static uint color(float creal, float cimag)
{
	float h, s, v, m, n, f, temp;
	int i;
	uint count = 0;
	float tm, sqlength, zreal = 0., zimag = 0.;

	do
		frac_next();
	while ((sqlength < MAX_SQLEN) && (count < MAX_ITER));

	//frac_next();
	//frac_next();

	if (count == MAX_ITER)
		return RGB(0,0,0);

	//h = count - log(log(sqrt(sqlength))) / log(2.);
	h = count - log(log(sqrt(sqlength))) / LOG2;

	/* h is given on [0, 6] or UNDEFINED.
	* s and v are given on [0, 1].
	*/
	s = v = 1.;
	h -= (floor(h / 6) * 6);

	i = (int) floor(h);
	f = h - i;

	if (!(i & 1))
		f = 1. - f;
	m = v * (1. - s);
	n = v * (1. - s * f);
	switch (i%6) {
	case 6:
	case 0: return RGB(v, n, m);
	case 1: return RGB(n, v, m);
	case 2: return RGB(m, v, n);
	case 3: return RGB(m, n, v);
	case 4: return RGB(n, m, v);
	case 5: return RGB(v, m, n);
	}
	return RGB(0,0,0);
}
#endif

Fractal::Fractal()
{
	// nothing
}
// added lwk
Fractal::Fractal(paroc_string machine)
{
	//rprintf("Object Fractal put on %s by ssh\n",(const char *)paroc_system::GetHost());
}

Fractal::~Fractal()
{
	// nothing
}


void Fractal::generate(int width, int height,
					   float realMin, float realScale, float imagMin, float imagScale,
					   int tile, Screen &screen)
{
	float creal, cimag;
	int v[width];

	for (int iy=0; iy<height; iy++) {
		for (int ix=0; ix<width; ix++) {
			creal = realMin + realScale * ix;
			cimag = imagMin + imagScale * iy;
			v[ix] = color(creal, cimag);
			// Picture of a math function instead
			// v[ix] = RGB(.5+.5*sin(exp(creal*creal*10+cimag*cimag*10)), .5+.5*sin(2*cimag), .5+.5*sin(2*creal));
		}
		screen.newRow(tile, iy, width, v);
	}
	screen.endTile(tile);
	printf("End of slave on %s\n", (const char *)paroc_system::GetHost());
}
@pack(Fractal);
