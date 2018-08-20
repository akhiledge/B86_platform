/**To remove \n appended to the input taken from fgets*/
char *modify(char *str)
{
	while(*str){
		if(*str == '\n')
		*str = '\0';
		str++;
	} 
}
