#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"

void fraction_multiply(const fraction* a,const fraction* b,fraction* product)
/*This function does following operation:
 * a/b * c/d = ac/bd
 * if ac = 0, do 0/1
 * reduce result into lowest fraction. */
{
   product->denom = a->denom * b->denom;
   product->numer = a->numer * b->numer;

   if (product->numer==0) { product->denom=1; }
   else
     { fraction_reduce(product); }
}
