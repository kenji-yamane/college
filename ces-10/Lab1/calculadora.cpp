/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/

#include <stdio.h>
#include <stdlib.h>

// Function declaration
float simple_math(float a, float b, char c);

// Main function invokes simple_math
int main() {

  float result, a, b;
  char c;

  if (scanf("%f %c %f", &a, &c, &b) != 3 || (c != '+' && c != '-' && c != '/' && c != '*'))
  {
      printf("ERR");
  }
  else
  {
      result = simple_math(a, b, c);

      printf("%.1f\n", result);
  }

  return 0;
}

// Function definition
float simple_math(float a, float b, char c) {

  float p;

  if (c == '-')
  {
      p = a - b;
  }
  if (c == '+')
  {
      p = a + b;
  }
  if (c == '-')
  {
      p = a - b;
  }
  if (c == '*')
  {
      p = a*b;
  }
  if (c == '/')
  {
      p = a/b;
  }

  return p;
}
