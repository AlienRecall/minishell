# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 20:31:37 by lfrancav &        #+#    #+#              #
#    Updated: 2024/02/21 21:57:39 by lfrancav &       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS=-L/usr/local/opt/readline/lib
IDFLAGS+=-I/usr/local/opt/readline/include

PARSER_SRCS = $(wildcard parser/*.c)
BUILTINS_SRCS = $(wildcard builtins/*.c)
EXEC_SRCS = $(wildcard exec/*.c)
LIBFT_SRCS = $(wildcard libft/*.c)

SRCS = main.c utils.c signals.c logic.c $(LIBFT_SRCS) $(BUILTINS_SRCS) $(PARSER_SRCS) $(EXEC_SRCS)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
BUILD_DIR = outputs

define rainbow_print
$(foreach char,$(1),printf "\033[44m$(char) \033[0m")
endef


lmao: $(NAME)
	@$(call rainbow_print,Goat)
	@$(call rainbow_print,shell:)
	@$(call rainbow_print,COMPILED!)
	@$(call rainbow_print,🐐)
	@$(call rainbow_print,'LMAOOOOOOOO')
	@echo

all: lmao

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lreadline

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)/$(dir $<)
	$(CC) $(CFLAGS) $(IDFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re