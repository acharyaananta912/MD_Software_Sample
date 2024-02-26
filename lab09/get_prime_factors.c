#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"

// This functions returns makes an array of a prime factors of the fraction.

void get_prime_factors(int n,int prime_list[],int* num_primes)

	/*This function does following operations:
	 * initialize a num_prime as 0. This is a position holder.
	 * Takes the denominater or numerator of the fraction as "n".
	 * "n" is divided by 2. It continiously divides and updates "n"
	 * for example: "n" = 8, *num_prime = 3, prime_list = [2,2,2], "n" =1 
	 * Then "n" is divided by 3 upto the point when it is no more divisble.
	 * Then it is divisibe by 5,7,.. .. upto the point when when "i" is less than its square root. 
	 * if the last "n" is not divisible by anything but is greater than 2, returns that number. */
{
   *num_primes = 0;

   while (n%2==0)
   {
      prime_list[*num_primes] = 2;
      *num_primes = *num_primes + 1;
      n = n / 2;
   }

   for (int i = 3; i <= sqrt(n); i = i + 2)
   {
      while (n%i==0)
      {
         prime_list[*num_primes] = i;
         *num_primes = *num_primes + 1;
         n = n / i;
      }
   }

   if (n>2)
   {
      prime_list[*num_primes] = n;
      *num_primes = *num_primes + 1;
   }
}
