# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 12:40:11 by obouykou          #+#    #+#              #
#    Updated: 2020/11/12 11:48:31 by obouykou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = $(wildcard ./*.c)

HEADER = ./libft.h

OBJECT = $(FILES:.c=.o)

OBJECT_B = $(FBONUS:.c=.o)

FLAGS = -Wextra -Werror -Wall

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER)
	@ar rc $(NAME) $(OBJECT)
	@ranlib $(NAME)

%.o:%.c	$(HEADER)					
	@gcc -c $< $(FLAGS)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re : fclean all
