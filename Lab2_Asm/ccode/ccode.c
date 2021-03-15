#include <stdio.h>
#define ARR 5
#define M 3
 
int main(void)

{
    int a[ARR] = {2,3,10,5,3},number = 0, sum = 0, i;
    for(i = 0; i < ARR; i++)
        {if (a[i] > M)
            sum +=a[i];
            else if
            (a[i] < M)
            number +=1;
        }
    printf("%d\n%d\n", sum, number);
    return 0;
}
