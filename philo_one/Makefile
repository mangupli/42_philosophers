NAME = one

all:	$(NAME)

SRCS = main.c utils.c start.c

$(NAME): $(SRCS)
	gcc $(SRCS) -pthread -o $@

clean:
	rm -f $(NAME) #!!!! rewrite

fclean: clean

re: fclean all