/**
 * File              : left_rotate.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */
node   *
left_rotate(node *pivot)
{
	node   *temp = NULL;

	temp = (pivot->right);
	(pivot->right) = (temp->left);
	(temp->left) = (pivot);
	return temp;
}
