#include "ft_db.h"

char			**db_tbladdl(char **tbl, char *line, size_t nmembrs)
{
	size_t		i;
	char		**res;
	char		**tmp;

	i = -1;
	tmp = NULL;
	if (nmembrs > 1)
	{
		if (!(res = (char **)db_memalloc(sizeof(char *) * (nmembrs + 1))))
			return (NULL);
		tmp = res;
		while (++i < nmembrs - 1)
		{
			*tmp = strdup(*tbl);
			tbl++;
			tmp++;
		}
		*tmp = strdup(line);
		return (res);
	}
	if (!(res = (char **)db_memalloc(sizeof(char *) * 1)))
		return (NULL);
	*res = strdup(line);
	return (res);
}
