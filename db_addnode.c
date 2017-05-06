#include "ft_db.h"

static t_tnode	*prep_addtnode(t_dbnfo *db)
{
	t_tnode *elem;

	if (!(elem = (t_tnode *)db_memalloc(sizeof(t_tnode) + 1)))
		return (NULL);
	db_inittnode(elem);
	strcpy(elem->tbl_name, db->tbl_name);
	time(&elem->ctime);
	time(&elem->mtime);
	return (elem);
}

void			db_addtnoden(t_tnode **t_tree, t_dbnfo *db)
{
	t_tridbnode		tri;

	tri.ttmp = *t_tree;
	if (!(tri.elem = prep_addtnode(db)))
		return ;
	if (tri.ttmp)
	{
		while (tri.ttmp)
		{
			if ((tri.ntmp = tri.ttmp) && \
					strcmp(tri.elem->tbl_name, tri.ttmp->tbl_name) < 0)
			{
				if (!(tri.ttmp = tri.ttmp->left))
					tri.ntmp->left = tri.elem;
			}
			else
			{
				if (!(tri.ttmp = tri.ttmp->right))
					tri.ntmp->right = tri.elem;
			}
		}
	}
	else
		*t_tree = tri.elem;
}
