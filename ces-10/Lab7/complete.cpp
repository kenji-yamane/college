#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#if CHAR_BIT != 8
#error "weird char size"
#endif

int find(void *x, void *array, size_t n, size_t a, _Bool (*compare) (const void*, const void*))
{
    n /= a;

    for (int i=0; i<(int)n; i++)
    {
        _Bool ret = compare (x, (char*)array + i*a);
        if (ret)
            return i;
    }

    return -1;
}

// return true if a=b (values)
_Bool compare_int (const void *a, const void *b)
{
    return *(int*)a == *(int*)b ? 1 : 0;
}

// return true if a=b (values)
_Bool compare_float (const void *a, const void *b)
{
    return *(float*)a == *(float*)b ? 1 : 0;
}

int main() 
{
    int vint[] = {1, 5, 10, 70, 3}, xint = 5;
    float vfloat[] = {1.3, 5.2, 10.1, 70.0, 3.3}, xfloat = 3.3;

    printf("vint[1]=vint[%d]=%d\n", find(&xint, (void*)vint, sizeof(vint), sizeof(*vint), compare_int), xint);
    printf("vfloat[4]=vfloat[%d]=%.1f\n", find(&xfloat, (void*)vfloat, sizeof(vfloat), sizeof(*vfloat), compare_float), xfloat);
}

