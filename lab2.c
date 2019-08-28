#include <stdio.h>
#include <stdlib.h>

int main() {
    char band1, band2;
    //double multi,toler; // multi - multiplier, toler - tolerance
    printf("Please enter 1st number:\n");
    scanf("%c", &band1);
    printf("Please enter 2nd number:\n");
    scanf("%c", &band2);
    
    printf ("Resistor bands:");
    if(band1 == 'k'|| band2 == 'k')
    {
     printf(" Black");
    }
    else if(band1 == 'b'|| band2 == 'b')
      {
        printf(" Brown");
      }
    else if(band1 == 'r'|| band2 == 'r')
    {
         printf(" Red");
     }
}