// Main entry point.
// Also contains some utility functions and keeps the thing running.

#include "common.h"

// my contribution to those in the Avoid Using C++ Front
// and the C++ Should Die A Horrible Death In A Fire Front.
void (*fptr_logic)(void) = NULL; // called every 50Hz when possible
void (*fptr_video)(void) = NULL;

/* returncode = int main(int argc, char *argv[]):
 * Entry point into this wonderful program.
 */
int main(int argc, char *argv[])
{
	if(sys_init())
		return 1;
	
	atexit(sys_exit);
	
	if(network_init())
		return 1;
	
	atexit(network_exit);
	
	printf("************************************************************\n");
	printf("FRench INGEnuity (C) 2010, BattleOfTheBits.org\n");
	printf("Based on CreepSmash available @ creepsmash.com (english ver)\n");
	printf("Licensed under GPLv3 - see LICENCE file for text\n");
	printf("************************************************************\n");
	
	fptr_logic = menu_fptr_init;
	fptr_video = NULL;
	
	sys_main();
	
	return 0;
}
END_OF_MAIN(); /* Allegro requirement */
