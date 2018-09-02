/*
 * File:getindex.c
 * Author:shrishail satihal
 * Description:function for getting index of each string
 * Date:20-7-18
 * last modified:23-8-18
 * last modified by:shrishail satihal <s.shrishail@globaledgesoft.com>
 */

int get_index(char ch) /*function definition for getting index of each
string which takes an argument character and returns an integer*/
{
    if ((ch >= 'a') && (ch <= 'z')) { /*if ch is between a to z return ch-a*/
	return (ch - 'a');
    } else if ((ch >= 'A') && (ch <= 'Z'))
	return (ch - 'A'); /*else return ch-A*/

    else if ((ch >= '0') && (ch  <= '9'))
	return ((ch+26) - '0');

    else
	return 37;

}
