#ifndef __FRACTION_H__
#define __FRACTION_H__

typedef struct fraction fraction;

/* make structure
 * fraction: name of the structure
 * fraction: name the structure fraction as fraction */

struct fraction
{
	/*inside a fraction structure there consists two integer
	 * numer: an integer that represents the numeretor of the fraction.
	 * denom: an integer that represents the denominator of the fraction. */
   int numer; int denom;
};

void fraction_add(const fraction* a,const fraction* b,fraction* sum);
void fraction_subtract(const fraction* a,const fraction* b,fraction* difference);
void fraction_multiply(const fraction* a,const fraction* b,fraction* product);
void fraction_divide(const fraction* a,const fraction* b,fraction* quotient);
void fraction_reduce(fraction* sum);
void get_prime_factors(int n,int prime_list[],int* num_primes);


#endif
