#include "ft_db.h"

static t_enode	*prep_addenode(t_dbnfo *info)
{
	t_enode *elem;

	if (!(elem = (t_enode *)db_memalloc(sizeof(t_enode) + 1)))
		return (NULL);
	db_initenode(elem);
	strcpy(elem->ename, info->key_name);
	strcpy(elem->ename, info->key_name);
	time(&elem->mtime);
	time(&elem->ctime);
	if (!(elem->cmembr = db_tbldup(info->val, db_tbllen(info->val))))
		return (NULL);
	return (elem);
}

void			db_addenoden(t_enode **entries, t_dbnfo *info)
{
	t_trienode		tri;

	tri.ttmp = *entries;
	if (!(tri.elem = prep_addenode(info)))
		return ;
	if (tri.ttmp)
	{
		while (tri.ttmp)
		{
			if ((tri.ntmp = tri.ttmp) && \
					strcmp(tri.elem->ename, tri.ttmp->ename) < 0)
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
		*entries = tri.elem;
}
