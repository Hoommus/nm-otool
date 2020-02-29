# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtarasiu <vtarasiu@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 16:12:23 by vtarasiu          #+#    #+#              #
#    Updated: 2020/02/29 16:20:20 by vtarasiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

CC = clang

FLAGS = -DSH=\"$(NAME)\" \
               -Wall  \
               -Wextra \
               -Werror -g #-fsanitize=address

LIB_DIR = ../../lib
INCLUDE_DIR = ../../include

LIB_INCLUDE = -I $(LIB_DIR)/libft \
              -I $(LIB_DIR)/libprintf/include

INCLUDE = -I $(INCLUDE_DIR) $(LIB_INCLUDE)

HEADER = -I $(INCLUDE_DIR)/ $(LIB_INCLUDE)
SRC_DIR = ./
OBJ_DIR = ./obj/

LIBFT_DIR = $(LIB_DIR)/libft
PRINTF_DIR = $(LIB_DIR)/ft_printf
PRINTF_LIB_NAME = libftprintf.a

COMMON_DIR = ../common
COMMON_LIB = $(COMMON_DIR)/taskmasterlib.a

NM_SRC = main.c \
			 process_handling.c \
			 ft_vector.c

CONFIG_DIR = config/
CONFIG_SRC = config_load.c

NETWORK_DIR = network/
NETWORK_SRC = sockets_manipulations.c client_interactions.c thread_pool.c \
              serve_invalid.c \
              serve_status.c \
              serve_handshake.c \
              serve_stop.c

OBJ = $(addprefix $(OBJ_DIR), $(NM_SRC:.c=.o))                        \
      $(addprefix $(OBJ_DIR)$(CONFIG_DIR), $(CONFIG_SRC:.c=.o))           \
      $(addprefix $(OBJ_DIR)$(NETWORK_DIR), $(NETWORK_SRC:.c=.o))

all: $(NAME)

standalone: libs $(NAME)

$(NAME): prepare $(OBJ) $(PRINTF_DIR)/$(PRINTF_LIB_DIR)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(HEADER) \
	$(PRINTF_DIR)/$(PRINTF_LIB_NAME) $(JSON_LIB_DIR)/$(JSON_LIB_NAME_STATIC) \
	$(COMMON_LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) $(HEADER) -o $@ -c $< ;

prepare:
	@mkdir -p $(OBJ_DIR)$(CONFIG_DIR)
	@mkdir -p $(OBJ_DIR)$(NETWORK_DIR)

$(PRINTF_DIR)/$(PRINTF_LIB_DIR):
	make -C $(PRINTF_DIR)/

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
