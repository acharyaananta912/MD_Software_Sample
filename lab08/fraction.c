#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct fraction fraction;
struct fraction
{
   int numer; int denom;
};
void fraction_reduce(fraction* sum);
void get_prime_factors(int n, int prime_list[], int* num_primes);

typedef struct proper_fraction proper_fraction;
struct proper_fraction
{
   int whole; int numer; int denom;
};

void make_proper_fraction(const fraction* sum)
{
   proper_fraction proper;
   proper.whole = sum->numer / sum->denom;
   proper.numer = abs(sum->numer) % sum->denom;  // Use abs to handle negative numerators
   proper.denom = sum->denom;

   if (sum->numer < 0)
   {
      // Handle negative numerators and whole parts
      if (proper.whole != 0)
      {
         printf(" -%i %i/%i", abs(proper.whole), proper.numer, proper.denom);
      }
      else
      {
         printf(" -%i/%i", proper.numer, proper.denom);
      }
   }
   else
   {
      if (proper.whole != 0)
      {
         printf(" %i %i/%i", proper.whole, proper.numer, proper.denom);
      }
      else
      {
         printf(" %i/%i", proper.numer, proper.denom);
      }
   }
}


void fraction_add(const fraction* a,const fraction* b,fraction* sum)
{
   sum->denom = a->denom * b->denom;
   sum->numer = a->numer * b->denom + b->numer * a->denom;

   if (sum->numer==0) { sum->denom=1; }
   else
     { fraction_reduce(sum); }
}

void fraction_subtract(const fraction* a,const fraction* b,fraction* difference)
{
   difference->denom = a->denom * b->denom;
   difference->numer = a->numer * b->denom - b->numer * a->denom;

   if (difference->numer==0) { difference->denom=1; }
   else
     { fraction_reduce(difference); }
}

void fraction_multiply(const fraction* a,const fraction* b,fraction* product)
{
   product->denom = a->denom * b->denom;
   product->numer = a->numer * b->numer;

   if (product->numer==0) { product->denom=1; }
   else
     { fraction_reduce(product); }
}

void fraction_divide(const fraction* a,const fraction* b,fraction* quotient)
{
   quotient->denom = a->denom * b->numer;
   quotient->numer = a->numer * b->denom;

   if (quotient->numer==0) { quotient->denom=1; }
   else
     { fraction_reduce(quotient); }
}

void fraction_reduce(fraction* sum)
{
   void get_prime_factors(int n,int prime_list[],int* num_primes);

   if ( sum->denom < 0 )
   { sum->numer = -sum->numer;
     sum->denom = -sum->denom; }
   
   int prime1[100]; int num_prime_1;
   int msign1 = 1; if (sum->numer < 0) { msign1 = -1; }
   sum->numer = abs(sum->numer);
   get_prime_factors(sum->numer,prime1,&num_prime_1);

   int prime2[100]; int num_prime_2;
   get_prime_factors(sum->denom,prime2,&num_prime_2);

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

void get_prime_factors(int n,int prime_list[],int* num_primes)
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

   

int main()
{
   fraction a,b,a1,b1,a2,b2,a3,b3,
            sum,sum1,sum2,sum3,
            difference, difference1, difference2, difference3, 
            product, product1, product2, product3,
            quotient, quotient1, quotient2, quotient3;

   a.numer = 1; a.denom = 10;
   b.numer = 5; b.denom = 3;

   a1.numer = -1; a1.denom = 10;
   b1.numer = -5; b1.denom = 3;

   a2.numer = 1; a2.denom = 10;
   b2.numer = -5; b2.denom = 3;

   a3.numer = -1; a3.denom = 10;
   b3.numer = 5; b3.denom = 3;

   fraction_add(&a,&b,&sum);
   fraction_add(&a1,&b1,&sum1);
   fraction_add(&a2,&b2,&sum2);
   fraction_add(&a3,&b3,&sum3);

   fraction_subtract(&a,&b,&difference);
   fraction_subtract(&a1,&b1,&difference1);
   fraction_subtract(&a2,&b2,&difference2);
   fraction_subtract(&a3,&b3,&difference3);

   fraction_multiply(&a,&b,&product);
   fraction_multiply(&a1,&b1,&product1);
   fraction_multiply(&a2,&b2,&product2);
   fraction_multiply(&a3,&b3,&product3);

   fraction_divide(&a,&b,&quotient);
   fraction_divide(&a1,&b1,&quotient1);
   fraction_divide(&a2,&b2,&quotient2);
   fraction_divide(&a3,&b3,&quotient3);

   printf("Test 1: \n");
   printf(" %i/%i + %i/%i = ",a.numer,a.denom,b.numer,b.denom);
   make_proper_fraction(&sum);
   printf("\n");

   printf(" %i/%i - %i/%i = ",a.numer,a.denom,b.numer,b.denom);
   make_proper_fraction(&difference);
   printf("\n");

   printf(" %i/%i * %i/%i = ",a.numer,a.denom,b.numer,b.denom);
   make_proper_fraction(&product);
   printf("\n");

   printf(" %i/%i / %i/%i = ",a.numer,a.denom,b.numer,b.denom);
   make_proper_fraction(&quotient);
   printf("\n");
   printf("\n");


   printf("Test 2: \n");

   printf(" %i/%i + %i/%i = ",a1.numer,a1.denom,b1.numer,b1.denom);
   make_proper_fraction(&sum1);
   printf("\n");

   printf(" %i/%i - %i/%i = ",a1.numer,a1.denom,b1.numer,b1.denom);
   make_proper_fraction(&difference1);
   printf("\n");

   printf(" %i/%i * %i/%i = ",a1.numer,a1.denom,b1.numer,b1.denom);
   make_proper_fraction(&product1);
   printf("\n");

   printf(" %i/%i / %i/%i = ",a1.numer,a1.denom,b1.numer,b1.denom);
   make_proper_fraction(&quotient1);
   printf("\n");
   printf("\n");


   printf("Test 3: \n");

   printf(" %i/%i + %i/%i = ",a2.numer,a2.denom,b2.numer,b2.denom);
   make_proper_fraction(&sum2);
   printf("\n");

   printf(" %i/%i - %i/%i = ",a2.numer,a2.denom,b2.numer,b2.denom);
   make_proper_fraction(&difference2);
   printf("\n");

   printf(" %i/%i * %i/%i = ",a2.numer,a2.denom,b2.numer,b2.denom);
   make_proper_fraction(&product2);
   printf("\n");

   printf(" %i/%i / %i/%i = ",a2.numer,a2.denom,b2.numer,b2.denom);
   make_proper_fraction(&quotient2);
   printf("\n");
   printf("\n");


   printf("Test 4: \n");

   printf(" %i/%i + %i/%i = ",a3.numer,a3.denom,b3.numer,b3.denom);
   make_proper_fraction(&sum3);
   printf("\n");

   printf(" %i/%i - %i/%i = ",a3.numer,a3.denom,b3.numer,b3.denom);
   make_proper_fraction(&difference3);
   printf("\n");

   printf(" %i/%i * %i/%i = ",a3.numer,a3.denom,b3.numer,b3.denom);
   make_proper_fraction(&product3);
   printf("\n");

   printf(" %i/%i / %i/%i = ",a3.numer,a3.denom,b3.numer,b3.denom);
   make_proper_fraction(&quotient3);
   printf("\n");

   return 0;
}
