/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <vtarasiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:00:41 by vtarasiu          #+#    #+#             */
/*   Updated: 2020/02/29 20:34:11 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "common.h"
#include "nm.h"

void					close_file(struct s_file *file)
{

}

static void					get_flags(struct s_file *file)
{

}

int						open_file(const char *name, struct s_file *dest)
{
	int				fd;
	struct stat		s;

	ft_bzero(dest, sizeof(*dest));
	fd = open(name, O_RDONLY);
	if (fd < 0 || fstat(fd, &s) ||
		!(dest->content = mmap(NULL, s.st_size, PROT_READ, 0, fd, 0)))
		return (ft_printf("nm: %s: %s\n", name, strerror(errno)), errno);
	dest->filename = name;
	dest->size = s.st_size;

	return (0);
}


int						parsenprint(struct s_file *state)
{

	return (0);
}

int						nm_archive();
int						nm_single();


int						main(int argc, char *argv[])
{
	int		i;

	i = 0;
	if (argc == 1)
		argv[argc++] = "a.out";
	while (++i < argc)
	{

	}
	return 0;
}
