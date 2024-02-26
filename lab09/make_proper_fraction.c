#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"
#include "properfraction.h"

// This function converts the improper fraction into a proper fraction.

void make_proper_fraction(const fraction* sum)

	/* proper_fraction is renamed proper for simplicity 
	 * integer fraction of the "a/b" is done and stored as whole number.
	 * The whole number can be negative or positive.
	 * remainder of "a/b" is stored as numerator.
	 * denominator remains same.
	 * if*/
{
   proper_fraction proper;
   proper.whole = sum->numer / sum->denom;
   proper.numer = abs(sum->numer) % sum->denom;  // Use abs to handle negative numerators
   proper.denom = sum->denom;

   /* if numerator from +- = 0 returns 0
    * if numerator from +- != 0, performs operations
    * if the fraction is already proper, returns the same input.
    * if the fraction is not proper but the "*" or "/" is perfectly divisible returns whole number.
    * if the fraction is not proper and it is still a fraction after division returns a proper fraction. */

   if (sum->numer == 0)
   {
	   printf("0");
   }
   else
   {
	   if (proper.whole == 0)
	   {
		   printf("%i/%i", sum->numer, sum->denom);
	   }
	   else
		   if (proper.numer != 0)
		   {
			   printf("%i %i/%i", proper.whole, proper.numer,proper.denom);
		   }
		   else
		   {
			   printf("%i", proper.whole);
		   }
   }
}
