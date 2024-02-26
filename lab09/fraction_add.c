#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"
void fraction_add(const fraction* a,const fraction* b,fraction* sum)

	/*This function adds two fractions:
	 * Inputs: fraction* a, a has numer and denom term
	 * a, b, sum are pointers to struct fraction, with * it creates copies of strut function
	 *  a/b + c/d = (ad + bc)/(bd) 
	 * if ad + bc = 0, return 0/1 
	 * Then reduce above result. */
{
   // -> is used for pointers otherwise sum.denom would work
   sum->denom = a->denom * b->denom;
   sum->numer = a->numer * b->denom + b->numer * a->denom;

   if (sum->numer==0) { sum->denom=1; }
   else
     { fraction_reduce(sum); }
}
