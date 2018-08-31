
/**
 * File              : all_keyboard_led.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */

/**
 *@brief control keyboard leds using keyboard
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#define BUF_SIZE 16				/*size of buffer */

/**@brief opening the brightness file for each keyboard led and changing the
 * state of led as for user input
 **/
int
main(void)
{
	int     fd[3];
	int     led;
	char   *input = NULL;
	char   *user_input = NULL;

	fd[0] = open("/sys/class/leds/input2::capslock/brightness", O_WRONLY);
	if (-1 == fd[0]) {
		printf("open failed for caps\n ");
		return 0;
	}

	fd[1] = open("/sys/class/leds/input2::numlock/brightness", O_WRONLY);
	if (-1 == fd[1]) {
		printf("open failed for num\n ");
		close(fd[0]);
		return 0;
	}

	fd[2] = open("/sys/class/leds/input2::scrolllock/brightness", O_WRONLY);
	if (-1 == fd[2]) {
		printf("open failed for scroll\n ");
		close(fd[0]);
		close(fd[1]);
		return 0;
	}
#if 0
	int     fd_ide = open("/sys/class/leds/input2::capslock/trigger",
			O_WRONLY);

	if (-1 == fd_ide) {
		printf("open failed\n ");
		return 0;
	}

	char   *act = "disk-activity";

	write(fd_ide, act, 13);
#endif

	user_input = calloc(1, sizeof(char) * BUF_SIZE);

	while (true) {
		fputs("enter an option", stdout);
		fputs("1.capslock 2.numlock 3.scrolllock 4.exit\n", stdout);

		led = atoi(fgets(user_input, BUF_SIZE, stdin)) - 1;
		if (led > 2) {
			fputs("invalid option\n", stdout);
			continue;
		}
		if (led == 4) {
			free(user_input);
			user_input = NULL;
			return 0;
		}

		lseek(fd[led], 0, SEEK_SET);
		fputs("off-0 on-1\n", stdout);

		input = (atoi(fgets(user_input, BUF_SIZE, stdin)) == 1 ? "1" : "0");

		if (-1 == write(fd[led], input, 1)) {
			printf(" write failed\n");
		}
	}

	printf(" completed\n");
	free(user_input);
	user_input = NULL;
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);

/*     close (fd_ide);*/
	return 0;
}
