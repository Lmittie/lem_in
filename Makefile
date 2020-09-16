# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/14 21:30:04 by acarlett          #+#    #+#              #
#    Updated: 2020/09/16 16:36:51 by acarlett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =		-Wall -Wextra -Werror

DIR_SRC =	srcs

DIR_INC =	includes

DIR_LIB =	libft

NAME = 		lem_in

SOURCES =	$(DIR_SRC)/adjacency_matrix.c \
			$(DIR_SRC)/checkers.c \
			$(DIR_SRC)/deleting.c \
			$(DIR_SRC)/main.c \
			$(DIR_SRC)/parse_ants_number.c \
			$(DIR_SRC)/parse_links.c \
			$(DIR_SRC)/parse_map.c \
			$(DIR_SRC)/parse_rooms.c \
			$(DIR_SRC)/room_list.c \
			$(DIR_SRC)/dinic_algorithm.c \
			
INCLUDES = 	$(DIR_INC)/lem_in.h \

OBJECTS =	$(patsubst %.c,%.o,$(SOURCES))


all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C libft all
	@gcc -o $(NAME) $(SOURCES) -I $(INCLUDES) libft/libft.a

%.o: %.c $(INCLUDES)
	@cc -I $(INCLUDES) $< -c -o $@

clean:
	@rm -rf $(OBJECTS)
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

val: all clean
	valgrind --leak-check=full ./$(NAME)

lem: all
	@./$(NAME) < test