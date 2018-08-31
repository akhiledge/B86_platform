/**
 * File              : inorder.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */
bool
inorder(node *subtree_root)
{
	if (subtree_root != NULL) {
		inorder(subtree_root->left);
		printf(" %d(%s)", (subtree_root->value),
				(subtree_root->color) ? "black" : "red");
		inorder(subtree_root->right);
	}
	return true;
}
