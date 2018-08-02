/**Hash function to get index from key*/

int hash_func(char ch)
{
	if((ch >= 'a') && (ch <= 'z'))			///if initial character is lowercase
		return (ch - 'a');					///index is (ch - 97)
	else if((ch >= 'A') && (ch <= 'Z'))		///if initial character is uppercase
		return(ch - 'A');					///index is (ch - 65)

	else if((ch >= '0') && (ch <= '9'))		///if initial character is number
		return(ch + 26 - '0');
	else									///special characters
		return 37;

}
