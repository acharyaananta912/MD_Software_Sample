#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"


void fraction_subtract(const fraction* a,const fraction* b,fraction* difference)
/* This function does following operation.
 * a/b - c/d = (ad - bc)/(bd)
 * if ad - bc = 0, do 0/1 
 * reduce the difference into lowest fraction. */
{
   difference->denom = a->denom * b->denom;
   difference->numer = a->numer * b->denom - b->numer * a->denom;

   if (difference->numer==0) { difference->denom=1; }
   else
     { fraction_reduce(difference); }
}
