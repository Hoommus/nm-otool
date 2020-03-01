/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:57:37 by vtarasiu          #+#    #+#             */
/*   Updated: 2020/03/01 16:15:23 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "common.h"

# define F_32BIT         0x1U
# define F_NOSORT        0x2U
# define F_BSWAP         0x4U
# define F_ARCHIVE       0x8U
# define F_ARCHIVE_EXT  0x10U

struct		s_file
{
	uint32_t			flags;
	size_t				size;
	const char			*filename;
	void				*content;
};

struct		s_symbol
{
	size_t				address;
	char				*name;
	char				type;
	struct s_symbol		*next;
};

struct		s_macho
{
	uint32_t			nm_flags;
	uint32_t			macho_flags;
	size_t				size;
	uint32_t			ncmds;
	uint32_t			sizeofcmds;
	const char			*filename;
	void	 			*content;
};

#endif
