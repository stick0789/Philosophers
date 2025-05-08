# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaacosta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 18:02:27 by jaacosta          #+#    #+#              #
#    Updated: 2024/11/06 18:46:39 by jaacosta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror ##cc -fsanitize=thread -g -Werror -Wall -Wextra *.c -o philo -lpthread
AR = ar -rcs ##cc -g -Werror -Wall -Wextra *.c -o philo
RM = rm -f

SRCS = 	   ft_strlen.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	   ft_isprint.c ft_tolower.c ft_toupper.c ft_strncmp.c ft_strchr.c \

HEADER = philo.h

OBJS = $(SRCS:.c=.o)

B_OBJS = $(B_SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) libft.h
		$(AR) $(NAME) $(OBJS)

%.o: %.c	$(HEADER) Makefile
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(B_OBJS)

fclean:		clean
		$(RM) $(NAME) $(OBS) $(B_OBJS)

re:
		$(RM) $(NAME) $(OBJS) $(B_OBJS)
		make all

bonus:		$(OBJS) $(B_OBJS) libft.h
		$(AR) $(NAME) $(OBJS) $(B_OBJS)


.PHONY: all, clean, fclean, re, bonus

