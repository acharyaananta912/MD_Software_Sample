#ifndef __PROPERFRACTION_H__
#define __PROPERFRACTION_H__

typedef struct proper_fraction proper_fraction;

/* defining a structure with a name.
 * proper_fraction: name of the structure to be named.
 * proper_fraction: name of the structure proper_fraction. */

struct proper_fraction
/*Defining the structure. Structure has three terms.
 * whole: the whole number of a proper fraction.
 * numer: numerator of the properfraction.
 * denom: denomenator of the properfraction*/
{
   int whole; int numer; int denom;
};

void make_proper_fraction(const fraction* sum);


#endif
