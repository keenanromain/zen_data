#include "ft_db.h"

void		db_deletevalue(t_tnode *t_tree, t_dbnfo *info)
{
	t_tnode *table;
	t_enode *entry;

	table = NULL;
	entry = NULL;
	if (!(table = db_searchtnode(t_tree, info)))
	{
		printf("ft_db: ERROR. Table not found.\n");
		return ;
	}
	if (!(entry = db_searchenode(table->entries, info)))
	{
		printf("ft_db: ERROR. Entry not found.\n");
		return ;
	}
	if (!info->val[0])
		return ;
	entry->cmembr = db_tblrmline(entry->cmembr, info->val[0], db_tbllen(entry->cmembr));
}

void		db_deletetbl(t_dbnfo *info)
{
	int		ret;
	char	*path;
	char	*filename;

	path = NULL;
	filename = NULL;
	if (!(filename = db_strjoin(info->tbl_name, ".tbl")))
		return ;
	if (!(path = db_strjoin("tbls/", filename)))
		return ;
	if ((ret = remove(path) == 0))
		printf("%s: %s has been deleted\n", G_TSYM, filename);
	else
		printf("%s: issues deleting %s\n", G_TSYM, filename);
	free(filename);
	free(path);
}
