#include <stdio.h>
#include <string.h>
#include "domen.h"

#define HELP_MSG \
"iputil - v0.0.1\n\
USAGE: iputil [OPTIONS] domen\n\
\n\
OPTIONS:\n\
-h|--help        Show this message."
#define HELP_DEF   puts(HELP_MSG);return 1
#define ARGEQ(x) strcmp(*argv,x)==0

int
main (int argc, char ** argv)
{
	Config cfg= {
		.domen = 0,
		.type  = 0,
	};

	for (;;) {
		if (argc==1 || !*argv) { break; }
		if (ARGEQ("-h") || ARGEQ("--help")) {
			HELP_DEF;
		} else {
			cfg.domen = *argv;
			cfg.type  = 1;
		}

		*argv++;
	}

	switch (cfg.type) {
	case 1:
		get_domen(cfg.domen);
		break;

	default:
		fprintf(stderr,"error: invalid args.\nSee --help.\n");
		return 2;
	}
}
