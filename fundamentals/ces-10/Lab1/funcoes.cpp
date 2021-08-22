/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Declaration
float vectorlength(float x, float y, float z);

// Main function invokes vectorlength to compute the length
int main() {
  float x, y, z, len;

  if (scanf("%f %f %f", &x, &y, &z) != 3)
    exit(-1);

  // Invoking your function
  len = vectorlength(x, y, z);

  printf("%f\n", len);

  return 0;
}

// Definition
float vectorlength(float x, float y, float z) {
  float p;

  p = sqrt(x*x + y*y + z*z);

  return p;
}
