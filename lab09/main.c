// importing all the required libraries and custom files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"
#include "properfraction.h"

int main()

{
	// need to declare all the variables that goes into fraction
	fraction a, b, sum, diff, product, ratio;

	a.numer = 1; a.denom = 10;
	b.numer = 5; b.denom = 3;

	/* runs fraction_add with given values.
	 * prints the input
	 * runs make_proper_fraction: it already contains print function. */

	fraction_add(&a, &b, &sum);
	printf(" %i/%i + %i/%i = ",a.numer,a.denom,b.numer,b.denom);
	make_proper_fraction(&sum); printf("\n");

	fraction_subtract(&a, &b, &diff);
        printf(" %i/%i - %i/%i = ",a.numer,a.denom,b.numer,b.denom);
        make_proper_fraction(&diff);printf("\n");

	fraction_multiply(&a, &b, &product);
        printf(" %i/%i * %i/%i = ",a.numer,a.denom,b.numer,b.denom);
        make_proper_fraction(&product);printf("\n");

	fraction_divide(&a, &b, &ratio);
        printf(" %i/%i / %i/%i = ",a.numer,a.denom,b.numer,b.denom);
        make_proper_fraction(&ratio);printf("\n");

	return 0;
}
