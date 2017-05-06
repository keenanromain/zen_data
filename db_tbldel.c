#include "ft_db.h"

void		db_tbldel(char **tbl)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = tbl;
	while (tmp[i])
	{
		if (tmp[i])
			free(tmp[i]);
		i++;
	}
	free(tbl);
	tbl = NULL;
}
