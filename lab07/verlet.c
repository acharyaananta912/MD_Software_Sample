// importing libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void Verlet(const int whichrun,
		const double u0,
		const double v0,
		const double dt,
		const int NumSteps)
/* This function solves Ordinary Differential Equation using a Verlet Scheme
 * Inputs:
 * whichrun -- count for run
 * u0       -- u at initial condition
 * v0       -- v at initial condition
 * dt       -- time interval
 * NumSteps -- Number of calculations to be performed */
{
	double u[NumSteps + 1];
	double v[NumSteps + 1];

	// Initial conditions
	
	u[0] = u0;
	v[0] = v0;
	
	for (int i =1; i <= NumSteps; i++)
	{
		double v_str = v[i - 1] + 0.5 * dt * (u[i - 1]-pow(u[i - 1],3)); // v* = v_n + 1/2*dt(u_n-u_n^3)
		u[i] = u[i - 1] + dt * v_str; //   u_n+1 = u_n + dt*v*
		v[i] = v_str  + 0.5 * dt * (u[i]-pow(u[i],3)); //   v_n = v* + 1/2*dt(u_n+1 - u_n+1^3)
	}
	char filename[15]; // Allocating 15 characters for filename
	sprintf(filename, "output%d.data", whichrun); // generating filename
	FILE* outputfile = fopen(filename, "w"); // generating file
	for (int i =0; i <= NumSteps; i++)
	{
		fprintf(outputfile, "%lf %lf\n", u[i],v[i]); // adding values to file
	}
	fclose(outputfile);
}

int main()
{
	const double Tfinal = 12.0;
	const int NumSteps = 1000;
	const double dt = Tfinal/NumSteps;

	Verlet(1,1.0,0.4,dt,NumSteps);
	Verlet(2,1.0,0.4,dt,NumSteps);
	Verlet(3,1.0,0.8,dt,NumSteps);
	Verlet(4,-1.0,0.6,dt,NumSteps);
	Verlet(5,-1.0,0.4,dt,NumSteps);


	return 0;
}
