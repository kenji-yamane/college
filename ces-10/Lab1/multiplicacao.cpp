#include <stdio.h>
#include <stdlib.h>

// Function declaration
void multi_table(unsigned int xsize, unsigned int ysize);

// Main function invokes multi_table
int main() {
  unsigned int xsize, ysize;

  if (scanf("%u %u", &xsize, &ysize) != 2)
    exit(1);

  multi_table(xsize, ysize);

  return 0;
}

void multi_table(unsigned int xsize, unsigned int ysize)
{
    unsigned int i, j, x;
    
    for (i = 1; i <= ysize; i++)
    {
        x = i;
        
        for (j = 1; j <= xsize; j++)
        {
            if (j != xsize)
            {
                printf("%4u", i);
                i = i + x;
            }
            else 
            {
                printf("%4u\n", i);
                i = x;
            }          
        }
    }    
}
