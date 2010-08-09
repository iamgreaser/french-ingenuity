// Networking code.

#include "common.h"

/* err = int network_init():
 * Initialise the network stuff.
 */
int network_init(void)
{
	printf("initialising network...");
	
#	ifdef WIN32
		// TODO: put in Winsock init crap here
		printf("FAIL - NO WINSOCK INIT CODE YET\n");
		return 1;
		//printf("OK! (next time use a real OS)\n");
#	else /* not WIN32 */
		printf("OK! (^5 for not using Wind0ze)\n");
#	endif /* WIN32 */
	
	
	return 0;
}

/* network_exit():
 * Shut down the network stuff.
 */
void network_exit(void)
{
#	ifdef WIN32
		// TODO: put in Winsock deinit crap here
#	endif /* WIN32 */
}
