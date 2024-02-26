#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"

// This function reduces the fraction to its lowest fraction.
// It uses another function to calculate the prime factor of the fraction.
void fraction_reduce(fraction* sum)
	
{
   // Takes prime factors from another function.
   void get_prime_factors(int n,int prime_list[],int* num_primes);

   /* Checks if denominator is negative. 
    * if a/b, -a/b, does not do anything.
    * if a/-b, does -a/b
    * if -a/-b, does a/b. */
   if ( sum->denom < 0 )
   { sum->numer = -sum->numer;
     sum->denom = -sum->denom; }

   /* From above operations only numerator can be negative.
    * Now a list of prime factors and number of prime factors are initialized
    * a sign holder is made to store whether numerator is negative or positive.
    * numerator is made positive (denominator is always positive).
    * Now gets the prime factor of numerator.
    * Then gets the prime factors of denominator. */
   int prime1[100]; int num_prime_1;
   int msign1 = 1; if (sum->numer < 0) { msign1 = -1; }
   sum->numer = abs(sum->numer);
   get_prime_factors(sum->numer,prime1,&num_prime_1);

   int prime2[100]; int num_prime_2;
   get_prime_factors(sum->denom,prime2,&num_prime_2);

   /* if any numerator and denominator prime factors are euqal inside the prime factor list.
    * Divides numerator by that prime factor.
    * And divide denominator by same prime factor. 
    * Finally the resultant of the numerator is multiplied by the sign
    * Result is the reduced fraction.  */
   int  i = 0; int  j = 0;
   int z1 = prime1[i]; int z2 = prime2[j];
   while (i<num_prime_1 && j<num_prime_2)
   {
      if (z1==z2)
      {
         sum->numer = sum->numer / z1;
         sum->denom = sum->denom / z2;
         
         i  = i + 1;
         j  = j + 1;
         z1 = prime1[i];
         z2 = prime2[j];
      }
      else
      {
         if (z1>z2)
         {
            j = j + 1;
            z2 = prime2[j];
         }
         else
         {
            i = i + 1;
            z1 = prime1[i];
         }
      }
   }
   sum->numer = sum->numer * msign1;
}
