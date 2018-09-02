/**
 * File              : find_root.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 14.07.2018
 * Last Modified Date: 01.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function to find root of red black tree
 * \return Returns root of tree
 * */
bst_t *find_root(bst_t *root)
{
    while (root->prev != NULL) {  /* Looping back till root */
	root = root->prev;
    }
    return root;
}
