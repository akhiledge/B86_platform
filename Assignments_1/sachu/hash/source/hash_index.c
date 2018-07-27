/**
 * @brief Function definition to find hash table index value
 * @param ch is a character storing first character of word
 * @return Returns index value(0-25) on success and -1 on error
 * */ 
int hash_index(char ch)
{
    switch(ch)
    {
        case 'A'...'Z':
            return ch - 65;
        case 'a'...'z':
            return ch - 97;
        default:
            return INVALID;
    }
}
