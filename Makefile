TARGET = pipex
SRCS = get_next_line.c pipex_cmd_name.c pipex_exec_cmd.c pipex_heredoc.c pipex_info_init.c pipex_main.c pipex_perror.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBDIR = ./libft
LIBFT = ./libft/libft.a

all:	$(TARGET)

$(TARGET):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(TARGET)

$(OBJS):	$(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

$(LIBFT):
	make -C $(LIBDIR)

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBDIR)

fclean:	clean
	rm -rf $(TARGET)
	make fclean -C $(LIBDIR)

re: fclean all

bonus:	all

.PHONY: all clean fclean re bonus