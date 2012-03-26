#include "screen.ph"


int main(int argc, char *argv[])
{
	char cmdline[32][32];
	for (int i=0; i<32 && i<argc; i++)
		strcpy(cmdline[i], argv[i]);

	Screen s;
	return s.run(argc, cmdline);
}
