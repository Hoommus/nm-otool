/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <vtarasiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:57:37 by vtarasiu          #+#    #+#             */
/*   Updated: 2020/02/29 20:32:56 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_NM_H
#define NM_OTOOL_NM_H

#include "common.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#define F_32BIT      0x1
#define F_NOSORT     0x2
#define F_BIG_ENDIAN 0x4

struct		s_file
{
	uint32_t			flags;
	size_t				size;
	const char			*filename;
	void				*content;
};

struct		s_symbol
{
	size_t				*address;
	char				*name;
	char				type;
	struct s_symbol		*next;
};

struct		macho_file
{

};

#endif //NM_OTOOL_NM_H
