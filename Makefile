NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

# Directories

SRC_DIR = src/
INCLUDE_DIR = include/
OBJ_DIR = obj/

# Files

SRCS = main.c philo_utils.c init.c time.c simulation.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
DEPS = $(OBJS:%.o=%.d)
INCLUDES = -I$(INCLUDE_DIR)

# Rules

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all fclean clean re
