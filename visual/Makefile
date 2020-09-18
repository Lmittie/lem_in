# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/18 15:55:20 by acarlett          #+#    #+#              #
#    Updated: 2020/09/18 19:39:00 by acarlett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =		-Wall -Werror -Wextra

SDL_LIB =	-L ~/.brew/lib -lSDL2

DIR_SRC =	srcs

DIR_LIB =	../libft

DIR_INC =	includes

NAME =		visualizer

LIB_NAME =	$(DIR_LIB)/libft.a

INC_NAME =	$(DIR_INC)/visualizer.h

SOURCES =	$(DIR_SRC)/main.c \
			$(DIR_SRC)/random.c \
			$(DIR_SRC)/flow_color.c 

OBJECTS =	$(patsubst %.c,%.o,$(SOURCES))

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(DIR_LIB)
	@cc -o $(NAME) $(SOURCES) -I $(DIR_INC) $(SDL_LIB) $(LIB_NAME)

%.o: %.c $(INC_NAME)
	@cc -I $(DIR_INC) $< -c -o $@

clean:
	@make -C $(DIR_LIB) clean
	@rm -rf $(OBJECTS)

fclean: clean
	@make -C $(DIR_LIB) fclean
	@rm -rf $(NAME)

re: fclean all