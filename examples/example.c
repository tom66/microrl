#include "../src/microrl.h"
#include "example_misc.h"
#include <stdio.h>
#include <string.h>

// create microrl object and pointer on it
microrl_t rl;
microrl_t *prl = &rl;

//*****************************************************************************
int main(void /*int argc, char ** argv*/) {
	init();
	struct microrl_config config = {
		.print = print,
		// set callback for execute
		.execute = execute,
#ifdef MICRORL_USE_COMPLETE
		// set callback for completion
		.get_completion = complet,
#endif
		// set callback for Ctrl+C
		.sigint = sigint,
	};
	microrl_init(prl, &config);
	microrl_set_execute_callback(prl, execute);
	while (1) {
		// put received char from stdin to microrl lib
		microrl_insert_char(prl, get_char());
	}
	return 0;
}
