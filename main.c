#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domen.h"
#include "me.h"

#define HELP_MSG \
"iputil - v0.0.1\n\
USAGE: iputil [OPTIONS] [domen]\n\
       iputil [OPTIONS] me\n\
\n\
OPTIONS:\n\
  -h|--help        Show this message.\n\
COMMANDS:\n\
  me               Shows your ips."
#define HELP_DEF   puts(HELP_MSG);exit(1)
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
		} else if(ARGEQ("me")) {
			cfg.type = 2;
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
	case 2:
		get_myself();
		break;

	default:
		fprintf(stderr,"error: invalid args.\nSee --help.\n");
		return 2;
	}
}
