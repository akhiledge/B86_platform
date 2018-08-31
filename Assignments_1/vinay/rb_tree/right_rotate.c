/**
 * File              : right_rotate.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */
node   *
right_rotate(node *pivot)
{
	node   *temp = NULL;

	temp = (pivot->left);
	(pivot->left) = (temp->right);
	(temp->right) = (pivot);
	return temp;
}
