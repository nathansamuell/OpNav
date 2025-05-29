#include <stdio.h>
#include "SpiceUsr.h"

int main() {

	/* local constnats */
	#define FILE_SIZE 128
	#define WORD_SIZE 80

	/* local variables */
	SpiceChar leapSeconds_KernelFile [FILE_SIZE] = "naif0012.tls";	// file name
	SpiceChar tdrssSPK_KernelFile [FILE_SIZE] = "TDRSS.bsp";	// file name
	SpiceChar observer[WORD_SIZE] = "EARTH";			// name of observer
	SpiceChar target[WORD_SIZE] = "-141";				// TDRSS-10 (ID -141 via the names file)
	SpiceChar time_UTC[WORD_SIZE] = "2023 JAN 01 12:00:00";		// Time we want position at
	SpiceDouble lightTime;						// not strictly needed for us, but needed for the function
	SpiceDouble time_ET;						// variable to store ephemeris time
	SpiceDouble stateData[6];					// used to store state data

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
	SpiceDouble orbitalConstants[8];
	SpiceDouble a;
	SpiceChar gravityKernel_KernelFile[FILE_SIZE] = "Gravity.tpc";
	
	/* load gravity kernel! */
	furnsh_c(gravityKernel_KernelFile);

	/* retrieve gravity constant mu from Gravity Kernel*/
	bodvrd_c("EARTH", "GM", 1, &elementsFound, &mu);

	/* ORBITAL ELEMENTS NEEDED 
	 * - theta (angle of orbit)
	 * - e (eccentricity)
	 * - a (semi-major axis)
	 * - Big Omega (orientation)
	 * - Little Omega (orientation)
	 * - i (orientation)*
	 * WHERE TO FIND
	 * e is orbitalConstants[1] according to SPICE docs*
	 * Big Omega, or RAAN (longitude of AN in SPICE docs*) is orbitalConstants[3]
	 * i is inclination in SPICE docs, or orbitalConstants[2]
	 * little omega is argument of perigee/periapsis, orbitalConstants[4] in SPICE docs
	 * from useful equations in orbital mechanics review, a (semi-major axis) = perifocal distance / (1 - e),
	 *	so computing should be straightforward! (perifocal distance is orbitalConstants[0] in SPICE docs)
	 * theta can be found from solving kepler's equation!
	 * */
	
	/* get orbital constants! */
	oscelt_c(stateData, time_ET, mu, orbitalConstants);

	/* calculate a */
	a = orbitalConstants[0] / (1.0 - orbitalConstants[1]);

	/* solve Kepler's equation for theta */
	// TODO: figure out if this is the correct approach
	

	/* print out our results */
	printf("\nPROBLEM B: ORBITAL ELEMENTS\n");
	printf("Theta: %23.16e\n", 23.894); // temp variable until I can calculate it
	printf("a: %23.16e\n", a);
	printf("e: %23.16e\n", orbitalConstants[1]);
	printf("Big Omega: %23.16e\n", orbitalConstants[3]);
	printf("i: %23.16e\n", orbitalConstants[2]);
	printf("Little Omega: %23.16e\n", orbitalConstants[4]);
	

	return 0;
}
