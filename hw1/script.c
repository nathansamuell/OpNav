#include <stdio.h>
#include "SpiceUsr.h"

int main() {

	/* local constnats */
	#define FILE_SIZE 128
	#define WORD_SIZE 80

	/* local variables */
	SpiceChar leapSeconds_KernelFile [FILE_SIZE] = "naif0012.tls";	// file name
	SpiceChar tdrssSPK_KernelFile [FILE_SIZE] = "TDRSS.bsp";		// file name
	SpiceChar observer[WORD_SIZE];									// name of observer
	SpiceChar target[WORD_SIZE];									// name of target, in our case will be TDRSS-10

	/* load kernels */
	furnsh_c(leapSeconds_KernelFile);
	furnsh_c(tdrssSPK_KernelFile);

	printf("Loaded kernels...\n\n");

	/* define observer and target */
	
	return 0;
}
