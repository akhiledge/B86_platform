/**
 * File              : keyboard.c
 * Author            : Yaragani Vamshi Krishna <vk.yaragani@globaledgesoft.com>
 * Date              : 17.08.2018
 * Last Modified Date: 20.08.2018
 * Last Modified By  : Yaragani Vamshi Krishna <vk.yaragani@globaledgesoft.com>
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>   

#define MAX 4

int main()
{
    FILE *fd_caps = NULL;
    FILE *fd_nums = NULL;
    FILE *fd_scroll = NULL;
    FILE *fd_max = NULL;
//    fd_max = fopen("/sys/class/leds/input2::capslock/max_brightness", "w");
  //      fputs("0", fd_max);
//    while(1){
    fd_caps = fopen("/sys/class/leds/input2::capslock/brightness", "w");
    fd_nums = fopen("/sys/class/leds/input2::numlock/brightness", "w");
    fd_scroll = fopen("/sys/class/leds/input2::scrolllock/brightness", "w");

    char *input = (char *)malloc( MAX * sizeof(char));
    assert(input);
//    char *input = "1";
//
        __fpurge(stdin);
        printf("Enter the value to leds\n on-1\t off-0:\n");
        fgets(input, MAX, stdin);

        fputs(input, fd_caps);
        fputs(input, fd_nums);
        fputs(input, fd_scroll);
        free(input);
        input = NULL;
 //       fclose();
 //   }


    return 0;
}
