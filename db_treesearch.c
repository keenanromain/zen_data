#include "ft_db.h"

t_tnode		*db_searchtnode(t_tnode *t_tree, t_dbnfo *info)
{
	t_tnode *tmp;

	tmp = t_tree;
	while (tmp)
	{
		if (strcmp(info->tbl_name, tmp->tbl_name) == 0)
			return (tmp);
		if (strcmp(info->tbl_name, tmp->tbl_name) < 0)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return (NULL);
}

t_enode		*db_searchenode(t_enode *e_tree, t_dbnfo *info)
{
	t_enode *tmp;

	tmp = e_tree;
	while (tmp)
	{
		if (strcmp(info->key_name, tmp->ename) == 0)
			return (tmp);
		if (strcmp(info->key_name, tmp->ename) < 0)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return (NULL);
}
