/**
 * @brief Function definition for creating node
 * @param i_file is a pointer storing base address of file name string
 * @param table is a pointer storing hash table base address
 * @param temp is a pointer storing base address of string
 * */
void create_database(char *i_file, hash **table, char *temp)
{
    int key;
    int ret;

    ///Function call to find index value
    key = hash_index(temp[MIN]);

    if(key == INVALID)           ///Invalid case
        return;

    ///Checking hash table index
    if(table[key] == NULL)
    {
        ///Index not filled case
        insert_first(&table[key], temp, i_file);
    }
    else
    {
        ///Index filled case-Checking for repetition
        ret = search_word(&table[key], temp);

        ///No repetition case
        if(ret == 0)
            insert_sorted(table, key, temp, i_file);

        //Repetition case
        else
            update_count(&table[key], temp, i_file); ///Function call to updae count
    }
}
