/**find the 10-digit prime number found in consecur=tive digits of e 
 * Google bill board puzzle solution
 * @author : Basava Prasad S J
 * @date : 23rd july 2018
 */
/* compile with -lm*/

///header file inclusion
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "header.h"
#include <string.h>

#define SIZE 11

long int prime (long int number){  //prime number definition
    int i = 2;
    int flag = 0;
    while (i < (sqrt (number))){       //till square root of the number
        if (number % i == 0){
            flag = 1;
            return 0;          //return false if number is not prime
        }
        i++;
    }
    if (flag == 0){
        return number;        //return number itself if number is prime
    }
}

int main (void)   
{
    //variables declarations   
    char *ptr = NULL;
    int index = 0;
    long int num = 0;
    long int res = 0;
    int count = 0;

    ptr = (char *) malloc (sizeof (char) * SIZE);//memory allocation
    assert (ptr); //validation for NULL pointer
    
    while (++count){         //untill count becomes false
        strncpy (ptr, (number + count), 10);   //copy the 10 numbers and compare
        *(ptr + 11) = '\0';  
        num = atol (ptr);
        res = prime (num);     //checking for prime or not
        if (res == num){
            printf ("%lu\n", res);   //result value
            break;
        }
    }
    return 0;
}
