#include "ft_db.h"

size_t		db_tbllen(char **tbl)
{
	size_t	i;
	char	**tmp;

	i = 0;
	if (tbl)
	{
		tmp = tbl;
		while (tmp[i])
			i++;
	}
	return (i);
}
