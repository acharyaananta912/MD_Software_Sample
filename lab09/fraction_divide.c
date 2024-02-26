#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"


void fraction_divide(const fraction* a,const fraction* b,fraction* quotient)
/*This function does following operation:
 * a/b / c/d = ad/bc 
 * if ad = 0, do 0/1
 * reduce the result to lowest fraction. */
{
   quotient->denom = a->denom * b->numer;
   quotient->numer = a->numer * b->denom;

   if (quotient->numer==0) { quotient->denom=1; }
   else
     { fraction_reduce(quotient); }
}
