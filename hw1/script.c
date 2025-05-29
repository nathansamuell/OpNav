#include <stdio.h>
#include "SpiceUsr.h"

int main() {

	/* local constnats */
	#define FILE_SIZE 128
	#define WORD_SIZE 80

	/* local variables */
	SpiceChar leapSeconds_KernelFile [FILE_SIZE] = "naif0012.tls";	// file name
	SpiceChar tdrssSPK_KernelFile [FILE_SIZE] = "TDRSS.bsp";		// file name
	SpiceChar observer[WORD_SIZE] = "EARTH";						// name of observer
	SpiceChar target[WORD_SIZE] = "-141";							// TDRSS-10 (ID -141 via the names file)
	SpiceChar time_UTC[WORD_SIZE] = "2023 JAN 01 12:00:00";			// Time we want position at
	SpiceDouble lightTime;											// not strictly needed for us, but needed for the function
	SpiceDouble time_ET;											// variable to store ephemeris time
	SpiceDouble stateData[6];										// used to store state data

	/* load kernels */
	furnsh_c(leapSeconds_KernelFile);
	furnsh_c(tdrssSPK_KernelFile);

	printf("Loaded kernels...\n");

	/* convert UTC to ET*/
	str2et_c(time_UTC, &time_ET);
	printf("Converted time...\n");


	/* get state of satellite */
	printf("Getting state...\n\n");
	spkezr_c(target, time_ET, "J2000", "NONE", observer, stateData, &lightTime);

	/* print state of satellite! */
	printf("PROBLEM A: STATE (Earth Centered):\n");
	printf("Position [X]: %23.16e\nPosition [Y]: %23.16e\nPosition [Z]: %23.16e\n\n", stateData[0], stateData[1], stateData[2]);
	printf("Velocity [X]: %23.16e\nVelocity [Y]: %23.16e\nVelocity [Z]: %23.16e\n\n", stateData[3], stateData[4], stateData[5]);

	/* problem 2, determine orbital elements */
	/* getting orbital elements from state using oscelt_c() found in the docs */
	/* local variables for problem 2*/

	// resuse sateliite data from problem 1
	// resuse ephemeris time from problem 1
	SpiceDouble mu; // found in Gravity.tpc
	SpiceInt elementsFound; // not needed, just here to satisfy bodvrd_c
	SpiceDouble orbitalElements[8];
	SpiceChar gravityKernel_KernelFile[FILE_SIZE] = "Gravity.tpc";
	
	/* load gravity kernel! */
	furnsh_c(gravityKernel_KernelFile);

	/* retrieve gravity constant mu from Gravity Kernel*/
	bodvrd_c("EARTH", "GM", 1, &elementsFound, &mu);

	/* get orbital constants! */
	oscelt_c(stateData, time_ET, mu, orbitalElements);
	

	return 0;
}
