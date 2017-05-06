#include "ft_db.h"

void	db_cleartree(t_tnode **tree)
{
	t_tnode		*tmp;

	tmp = *tree;
	if (!tree)
		return ;
	if (tmp->left)
		db_cleartree(&tmp->left);
	if (tmp->right)
		db_cleartree(&tmp->right);
	db_clearetree(&tmp->entries);
	free(tmp);
	tree = NULL;
}

void	db_clearetree(t_enode **tree)
{
	t_enode		*tmp;

	tmp = *tree;
	if (!tree)
		return ;
	if (tmp->left)
		db_clearetree(&tmp->left);
	if (tmp->right)
		db_clearetree(&tmp->right);
	free(tmp);
	tree = NULL;
}
