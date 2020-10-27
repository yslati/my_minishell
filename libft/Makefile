# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 12:40:11 by obouykou          #+#    #+#              #
#    Updated: 2020/10/26 11:39:03 by obouykou         ###   ########.fr        #
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
