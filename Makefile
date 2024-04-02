# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 21:19:50 by kiroussa          #+#    #+#              #
#    Updated: 2024/04/02 02:55:19 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	breakage.so

SRC				=	brk_allocs_count.c \
					brk_backtrace.c \
					brk_check_leaks.c \
					brk_fprintf.c \
					brk_hooks.c \
					brk_init.c \
					brk_insert_alloc.c \
					brk_log.c

SRC_FOLDER		=	src
OBJ_FOLDER		=	obj

OBJ				:= 	$(addprefix $(OBJ_FOLDER)/, $(SRC:.c=.o))
SRC				:=	$(addprefix $(SRC_FOLDER)/, $(SRC))

INCLUDE_DIR		= 	include

CC				=	clang
CFLAGS			= 	-Wall -Wextra -Werror -fPIC
ifeq ($(DEBUG), 1)
	CFLAGS		+=	-gdwarf-4
endif
COPTS			+= 	-I $(INCLUDE_DIR)/

RM				=	rm -rf

#
# Rules
#

all:			$(NAME)

$(NAME):		$(OBJ)
	$(CC) $(CFLAGS) $(COPTS) -shared -nostartfiles -o $(NAME) $(OBJ)

$(OBJ_FOLDER)/%.o:	$(SRC_FOLDER)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(COPTS) -c $< -o $@

clean:
	$(RM) $(OBJ_FOLDER)

fclean:			clean
	$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
