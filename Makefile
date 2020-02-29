# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtarasiu <vtarasiu@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 14:31:34 by vtarasiu          #+#    #+#              #
#    Updated: 2020/02/29 16:16:51 by vtarasiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM_MODULE = src/nm
OTOOL_MODULE = src/otool
COMMON_MODULE = src/common

NM_BINARY = ft_nm
OTOOL_BINARY = ft_otool

COMMON_NAME = libnmotool.a

LIB_DIR = lib

PRINTF_DIR = $(LIB_DIR)/libprintf
LIBFT_DIR = $(LIB_DIR)/libft

BINARIES = $(NM_MODULE)/$(NM_BINARY) $(OTOOL_MODULE)/$(OTOOL_BINARY)

all: libs
	make -C $(COMMON_MODULE)
	make -C $(NM_MODULE)
	make -C $(OTOOL_MODULE)
	mv $(NM_MODULE)/$(NM_BINARY) $(NM_BINARY)
	mv $(OTOOL_MODULE)/$(OTOOL_BINARY) $(OTOOL_BINARY)

libs:
	make -C $(LIBFT_DIR)/
	make -C $(PRINTF_DIR)/

clean:
	make -C $(COMMON_MODULE) clean
	make -C $(NM_MODULE) clean
	make -C $(OTOOL_MODULE) clean

fclean:
	make -C $(COMMON_MODULE) fclean
	make -C $(NM_MODULE) fclean
	make -C $(OTOOL_MODULE) fclean
	/bin/rm -f $(NM_BINARY)
	/bin/rm -f $(OTOOL_BINARY)

re: fclean all

love:
	@echo "Not all."

.PHONY: all clean fclean re