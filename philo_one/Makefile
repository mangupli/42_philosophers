# Compilation #

FLAGS = -Wall -Wextra -Werror -pthread

# Directories #

SRCS_DIR = ./srcs/
OBJS_DIR = ./objs/
INC_DIR = ./includes/
HEADER = $(INC_DIR)philo_one.h
LINK_INC = -I $(INC_DIR)

# Source files #

NAME = philo_one
SRCS = main.c utils.c start.c msg.c forks.c monitors.c libft.c

# Object files #

OBJS_FILES = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_FILES))

# Rules #

all:	$(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	gcc $(FLAGS) $(LINK_INC) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
