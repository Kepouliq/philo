NAME = philo

C_FILES = main.c\
			init.c\
			utils.c\
			routine.c\
			

SRCS = $(addprefix sources/,$(C_FILES))

CFLAGS = -Wall -Wextra -Werror -g3 -pthread

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Iincludes -I/usr/include -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Iincludes  -L/usr/lib -o $(NAME)

clean:
	rm -rf ${OBJS}


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re