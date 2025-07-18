NAME = philo

# Compilation

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories

SRC_DIR = src/
INCLUDE_DIR = include/
OBJ_DIR = obj/

# Files

SRCS = philo.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
DEPS = $(OBJS:%.o=%.d)

# Rules

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $< -o $@


