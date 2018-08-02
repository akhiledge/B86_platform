//#include"header.h"
//function definition for getting index
int get_index(char ch)                                                          
{                                                                               
	if((ch >= 'a') && (ch <= 'z')) ///if ch is between a to z return ch-a 
	{
		return (ch - 'a');      
	}              
	else if((ch >= 'A') && (ch <= 'Z'))                                                                      
		return (ch - 'A');    ///else return ch-A
	
	else if ((ch >= '0' ) && (ch  <= '9'))
		return ((ch+26) - '0');
	
	else
		return 37;
	                                                                               
}             
