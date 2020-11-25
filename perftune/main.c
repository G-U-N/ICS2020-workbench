#include <stdint.h>
#include <stdio.h>
#include <time.h>

int *sieve(int n);

clock_t start,total;


int main() {
  start=clock();
  
  int *primes = sieve(1000000);
  for (int *cur = primes, i = 0; *cur; cur++, i++) {
    printf("%8d", *cur);
    if (i % 8 == 7 || !*(cur + 1)) printf("\n");
}
total=clock()-start;
printf("%ld",total);
}