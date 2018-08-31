/**
 * File              : sibling.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */
node   *
sibling(node *child, node *parent)
{
	return ((parent->right) == child) ? (parent->left) : (parent->right);
}
