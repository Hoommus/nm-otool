/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:00:41 by vtarasiu          #+#    #+#             */
/*   Updated: 2020/03/01 19:19:39 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "common.h"
#include "nm.h"

void					close_file(struct s_file *file)
{
	munmap(file->content, file->size);
	ft_bzero(file, sizeof(*file));
}

static int				get_nm_flags(struct mach_header *header)
{
	uint32_t	flags;

	flags = 0;
	if (header->magic == MH_MAGIC)
		flags |= F_32BIT;
	else if (header->magic == MH_CIGAM)
		flags |= F_32BIT | F_BSWAP;
	else if (header->magic == MH_CIGAM_64)
		flags |= F_BSWAP;
	else if (!ft_memcmp(&header->magic, ARMAG, SARMAG))
		flags |= F_ARCHIVE | (ft_memcmp(&header->magic,
			ARMAG AR_EFMT1,ft_strlen(ARMAG AR_EFMT1)) ? 0 : F_ARCHIVE_EXT);
	else if (header->magic != MH_MAGIC_64)
		return (-1);
	return (flags);
}

int						open_file(const char *name, struct s_file *dest)
{
	int				fd;
	struct stat		s;

	ft_bzero(dest, sizeof(*dest));
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (ft_printf("\nnm: %s: %s\n", name, strerror(errno)));
	if (fstat(fd, &s) || !(dest->content = mmap(NULL, s.st_size, PROT_READ, 0, fd, 0)))
	{
		close(fd);
		return (ft_printf("\nnm: %s: %s\n", name, strerror(errno)));
	}
	dest->filename = name;
	dest->size = s.st_size;
	close(fd);
	return (0);
}

int						nm_archive(struct s_file *file, size_t offset)
{
	uint32_t		flags;
	struct s_file	inner;

	flags = get_nm_flags(file->content + offset);
	inner.content = (void *)file + sizeof(struct ar_hdr);
	inner.size = 0;
	return (0);
}

uint32_t __attribute__((always_inline))			bswap32(uint32_t x)
{
	return (__builtin_bswap32(x));
}

uint64_t __attribute__((always_inline))			bswap64(uint64_t x)
{
	return (__builtin_bswap64(x));
}

void					macho_populate(struct s_macho *dest,
	struct mach_header *header, uint32_t flags)
{
	const bool	bswap = flags & F_BSWAP;

	*dest = (struct s_macho){0};
	dest->nm_flags = flags;
	if (bswap)
	{
		dest->ncmds = __builtin_bswap32(header->ncmds);
		dest->sizeofcmds = __builtin_bswap32(header->sizeofcmds);
		dest->macho_flags = __builtin_bswap32(header->flags);
	}
	else
	{
		dest->ncmds = header->ncmds;
		dest->sizeofcmds = header->sizeofcmds;
		dest->macho_flags = header->flags;
	}
	dest->content = header;
}

bool					cmd_is_valid_nbr(uint32_t cmd)
{
	if (cmd == LC_LOAD_WEAK_DYLIB || cmd == LC_RPATH ||
		cmd == LC_DYLD_INFO_ONLY || cmd == LC_LOAD_UPWARD_DYLIB ||
		cmd == LC_MAIN ||
		cmd == LC_DYLD_EXPORTS_TRIE || cmd == LC_DYLD_CHAINED_FIXUPS)
		return (true);
	if (cmd == 0x18 || cmd == 0x1c || cmd == 0x1f || cmd == 0x22 ||
		cmd == 0x23 || cmd == 0x28 || cmd > 0x32)
		return (false);
	return (true);
}

int						cmd_validate(struct s_macho *macho, struct load_command *cmd)
{
	uint32_t cmd_nbr;

	if ((void *)cmd > (void *)macho + macho->size)
		return (ft_printf("nm: %s: %s\n", macho->filename,
			"invalid size or macho is truncated"));
	cmd_nbr = (macho->nm_flags & F_BSWAP) ? bswap32(cmd->cmd) : cmd->cmd;
	if (!cmd_is_valid_nbr(cmd_nbr))
		return (ft_printf("\nnm: %s: %#x\n", "invalid cmd", cmd_nbr));
//	if ((macho->nm_flags & F_32BIT) && cmd_nbr != LC_SEGMENT)
//		return (ft_printf("nm: %s: %s\n", macho->filename,
//			"invalid cmd in 32bit context"));
//	else if (cmd_nbr != LC_SEGMENT_64)
//		return (ft_printf("nm: %s: %s\n", macho->filename,
//			"invalid cmd in 64bit context"));
	return (0);
}

void					*nm_cmd_stride(struct s_macho *macho, void *cmd)
{
	if ((macho->nm_flags & F_32BIT))
		cmd += sizeof(struct segment_command);
	else
		cmd += sizeof(struct segment_command_64);
	return (cmd);
}

int						nm_cmd_foreach(struct s_macho *macho, void *first_cmd)
{
	size_t		i;

	i = 0;
	while (i < macho->ncmds)
	{
		if (cmd_validate(macho, first_cmd))
			return (1);

	}
	return (0);
}

int						nm_single(struct s_file *file, size_t offset)
{
	struct mach_header	*header;
	struct load_command	*first_cmd;
	struct s_macho		macho;
	uint32_t			flags;

	header = file->content + offset;
	flags = get_nm_flags(header);
	macho_populate(&macho, header, flags);
	first_cmd = (struct load_command *)((void *)header + (flags & F_32BIT) ?
												sizeof(struct mach_header) :
												sizeof(struct mach_header_64));
	return (nm_cmd_foreach(&macho, first_cmd));
}

int						nm(struct s_file *file, size_t offset)
{
	if ((file->flags = get_nm_flags(file->content + offset)))
		return (ft_printf("\nnm: %s: %s\n", file->filename,
			"The file was not recognized as a valid object file"));
	if ((file->flags & F_ARCHIVE) == F_ARCHIVE)
		nm_archive(file, offset);
	else
		nm_single(file, offset);
	return (0);
}

int						main(int argc, char *argv[])
{
	int				i;
	struct s_file	file;

	i = 0;
	if (argc == 1)
		argv[i--] = "a.out";
	while (++i < argc)
	{
		if (open_file(argv[i], &file))
			continue ;
		nm(&file, 0);
		close_file(&file);
	}
	return 0;
}
