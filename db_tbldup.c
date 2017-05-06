#include "ft_db.h"

char		**db_tbldup(char **tbl, int len)
{
	int		i;
	char	**res;
	char	**tmp;

	i = -1;
	if (!(res = (char **)db_memalloc(sizeof(char *) * (len + 1))))
		return (NULL);
	tmp = res;
	while (++i < len)
	{
		*tmp = strdup(*tbl);
		tbl++;
		tmp++;
	}
	return (res);
}

char		**db_tblrmline(char **tbl, char *rm, int len)
{
	int		i;
	char	**res;
	char	**tmp;

	i = -1;
	res = NULL;
	if (rm)
	{
		if (!(res = (char **)db_memalloc(sizeof(char *) * len)))
			return (NULL);
		tmp = res;
		while (++i < len)
		{
			if (strcmp(rm, *tbl) != 0)
			{
				*tmp = strdup(*tbl);
				tbl++;
				tmp++;
			}
			else
				tbl++;
		}
	}
	return (res);
}
