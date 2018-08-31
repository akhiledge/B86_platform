/**
 * File              : postorder.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */
bool
postorder(node *subtree_root)
{
	if (subtree_root != NULL) {
		postorder(subtree_root->left);
		postorder(subtree_root->right);
		printf(" %d(%s)", (subtree_root->value),
				(subtree_root->color) ? "black" : "red");
	}
	return;
}
