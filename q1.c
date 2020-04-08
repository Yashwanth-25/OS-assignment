#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a[10] = {143,86,1470,913,1774,948,1509,1022,1750,130};
    int prev = 0;
    int total = 0;
	
	for(int i = 0 ; i < 10 ; i++)
    {
        if(prev != 0)
        {
            total += abs(a[i] - prev);
            prev = a[i];
        }

        else    prev = a[i];
    }

    printf("a. FCFS: %d",total);
    return 0;
}
