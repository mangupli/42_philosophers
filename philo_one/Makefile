NAME = philo_one

all:	$(NAME)

SRCS = main.c

$(NAME): $(SRCS)
	gcc $(SRCS) -pthread -o $@

clean:
	rm -f $(NAME) #!!!! rewrite

fclean: clean

re: fclean all