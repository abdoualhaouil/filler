NAME= aalhaoui.filler

SRC= src/ft_lst_function.c \
	 src/read_map.c \
	 src/stack_queue.c \
	 src/filler.c \
	 src/main.c \
	 src/piece.c \
	 src/set_heatmap.c

OBJ= $(SRC:.c=.o)

GNLSRC= lib/get_next_line/get_next_line.c

GNLOBJ= $(GNLSRC:.c=.o)

CC= gcc
GCF= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(GCF) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME) : $(OBJ) $(GNLOBJ) include/filler.h lib/get_next_line/get_next_line.h
	make -C lib/libft
	make -C lib/ft_printf
	$(CC) $(GCF) $(OBJ) $(GNLOBJ) lib/libft/libft.a lib/ft_printf/libftprintf.a -o $(NAME)

.PHONY: clean
clean:
	make clean -C lib/libft
	make clean -C lib/ft_printf
	rm -fr $(OBJ) $(GNLOBJ)

.PHONY: fclean
fclean: clean
	make fclean -C lib/libft
	make fclean -C lib/ft_printf
	rm -fr $(NAME)

.PHONY: re
re: fclean all