CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

SRCS = env_mini/init_env.c				\
	   env_mini/extract_env.c			\
	   env_mini/extract_path.c			\
	   parsing/from_str_to_struct.c		\
	   parsing/init_commands.c			\
	   parsing/init_io.c				\
	   parsing/init_pipes.c				\
	   parsing/word_analysing.c			\
	   parsing/dollars_and_content.c	\
	   parsing/write_commands.c			\
	   prompt/interface.c				\
	   prompt/get_next_line.c			\
	   prompt/terminal.c				\
	   prompt/prompt_control.c			\
	   execution/pipex.c				\
	   execution/pipex_utils.c			\
	   execution/command_execution.c	\
	   execution/utils1.c	            \
	   execution/is_special_buildin.c   \
	   execution/many_fd.c				\
	   commands/exit.c					\
	   commands/env.c					\
	   commands/pwd.c					\
	   commands/export.c				\
	   commands/unset.c                 \
	   errors_and_exits.c				\
	   libft/utils.c					\
	   libft/ft_putstr.c				\
	   main.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
