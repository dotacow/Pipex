CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes

LIBDIR = libft
LIB = $(LIBDIR)/libft.a

SRC = pipex.c

SRCS :=  $(addprefix srcs/,$(SRC))
OFILES := $(addprefix ofiles/,$(SRC:.c=.o))

NAME = pipex



ofiles/%.o: srcs/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES) | $(LIB)
	$(CC) $(OFILES) -L$(LIBDIR) -lft -o $(NAME)

$(LIB):
	make -C $(LIBDIR)

clean:
	rm -rf ofiles
	make clean -C $(LIBDIR)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f $(NAME)

re: fclean all

dirs:
	mkdir -p ofiles

.PHONY: dirs all clean fclean re