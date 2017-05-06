#include "ft_db.h"

void			db_addorcreate(t_tnode **t_tree, t_dbnfo *file)
{
	t_tnode *table;
	t_enode *entry;

	entry = NULL;
	table = NULL;
	if (*t_tree != NULL && (table = db_searchtnode(*t_tree, file)))
	{
		if (!(entry = db_searchenode(table->entries, file)))
			db_addenoden(&table->entries, file);
		else
		{
			entry->cmembr = \
							db_tbladdl(entry->cmembr, *file->val, db_tbllen(entry->cmembr) + 1);
		}
	}
	else
	{
		db_addtnoden(t_tree, file);
		if (!(table = db_searchtnode(*t_tree, file)))
			return ;
		db_addenoden(&table->entries, file);
	}
}

int				db_fillnode(t_tnode **t_tree, FILE *p_tf)
{
	t_dbnfo		file;
	char		tmp[MXNAMLEN];
	char		**value;

	bzero(tmp, MXNAMLEN);
	db_initdbnfo(&file);
	if (!(fscanf(p_tf, "%s", tmp)))
		return (-1);
	strcpy(file.tbl_name, tmp);
	bzero(tmp, MXNAMLEN);
	if (!(fscanf(p_tf, "%s", tmp)))
		return (-1);
	file.nval = atoi(tmp);
	bzero(tmp, MXNAMLEN);
	if (!(fscanf(p_tf, "%s", tmp)))
		return (-1);
	file.ctime = atoi(tmp);
	bzero(tmp, MXNAMLEN);
	if (!(fscanf(p_tf, "%s", tmp)))
		return (-1);
	time(&file.mtime);
	bzero(tmp, MXNAMLEN);
	while (fscanf(p_tf, "%s", tmp) && *tmp != '\0')
	{
		if (tmp[0] == '|')
			break ;
		file.nargs++;
		value = db_strsplit(tmp, '|');
		strcpy(file.key_name, value[0]);
		if (!(file.val = db_tbldup(&value[1], db_tbllen(&value[1]))))
			return (-1);
		db_addorcreate(t_tree, &file);
		bzero(tmp, MXNAMLEN);
	}
	return (0);
}

int				db_filltree(t_tnode **t_tree, t_dbnfo *sort)
{
	int		i;
	FILE	*p_file;
	char	*dir;
	char	*tmp;

	i = -1;
	dir = NULL;
	tmp = NULL;
	while (sort->args[++i])
	{
		if (!(dir = db_strjoin("tbls/", sort->args[i])))
			return (-1);
		if (!(p_file = fopen(dir, "r")))
			continue ;
		db_fillnode(t_tree, p_file);
		fclose(p_file);
	}
	return (0);
}

int				db_populatedb(t_tnode **t_tree, FILE *p_dbf)
{
	size_t		xpctdn;
	t_dbnfo		sort;
	char		tmp[MXNAMLEN];

	bzero(tmp, MXNAMLEN);
	if (!(fscanf(p_dbf, "%s", tmp)))
		return (-1);
	xpctdn = atoi(tmp);
	bzero(tmp, MXNAMLEN);
	if (!(fscanf(p_dbf, "%s", tmp)))
		return (-1);
	if (*tmp != '0')
		sort.ctime = atoi(tmp);
	bzero(tmp, MXNAMLEN);
	if (!(fscanf(p_dbf, "%s", tmp)))
		return (-1);
	if (*tmp != '0')
		sort.mtime = atoi(tmp);
	bzero(tmp, MXNAMLEN);
	sort.nargs = sort.nval;
	while (fscanf(p_dbf, "%s", tmp) && *tmp != '\0')
	{
		if (tmp[0] == '|')
			break ;
		sort.nargs++;
		sort.args = db_tbladdl(sort.args, tmp, sort.nargs);
		bzero(tmp, MXNAMLEN);
	}
	db_filltree(t_tree, &sort);
	return (0);
}

void			db_loaddatabase(t_tnode **t_tree)
{
	FILE		*p_dbf;

	p_dbf = NULL;
	if (!(p_dbf = fopen("rtt.db", "r")))
	{
		if (!(p_dbf = fopen("rtt.db", "ab")))
			return ;
		fwrite("0\n0\n0\nNA", 8, 1, p_dbf);
		fclose(p_dbf);
		p_dbf = NULL;
	}
	if (p_dbf)
	{
		db_populatedb(t_tree, p_dbf);
		fclose(p_dbf);
	}
}
