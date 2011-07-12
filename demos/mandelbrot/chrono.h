#include <sys/time.h>


class Chronometer
{
private:
	double *lapTable, zero;
	char **textTable;
	int lapN, maxN, toSkip;
public:
	Chronometer(int nlaps);
	void skip(int s);
	void lap(const char *text);
	void lap(const char *text, int i);
	void dump();
	void dump(const char *fn);
};

extern Chronometer chronos;
