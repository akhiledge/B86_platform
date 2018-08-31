/**
 * File              : preorder.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */
bool
preorder(node *subtree_root)
{
	if (subtree_root != NULL) {
		printf(" %d(%s)", (subtree_root->value),
				(subtree_root->color) ? "black" : "red");
		preorder(subtree_root->left);
		preorder(subtree_root->right);
	}
	return;
}
