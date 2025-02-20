OUT = minishell

BUILTINS = $(addprefix builtins/, built-in.c cd.c echo.c env.c \
			 exit.c export.c export2.c pwd.c unset_2.c unset.c utils.c)
ENV = $(addprefix env/, env.c free_machine.c)
EXECUTOR = $(addprefix executor/, exec.c file_police.c open_files.c utils2.c utils.c)
EXPANDS = expands/expands.c
FILE_MANAGER = $(addprefix file_manager/, file_list.c here_utils.c heredoc.c)
PARSE_ERRORS = parse_errors/gprs_errors.c
PARSING = $(addprefix parsing/, gparce_save.c parse_utils.c prs_booleans.c)
SIGNALS = $(addprefix signals/, signal_handler.c)
SPLITTER = $(addprefix splitter/, ft_spliter.c spliter_utils.c)
SRC = minishell.c $(BUILTINS) $(ENV) $(EXECUTOR) $(EXPANDS) $(FILE_MANAGER) $(PARSE_ERRORS) $(PARSING) $(SIGNALS) $(SPLITTER)
SRC_OBJS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -g
HEADER = -I. -I$(LIBFT_DIR)
LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)libft.a

all: $(LIBFT) $(OUT)

$(LIBFT):
	@echo "Making Libft.."
	@make -C $(LIBFT_DIR)

$(OUT): $(SRC_OBJS)
	cc $(FLAGS) $(SRC_OBJS) $(HEADER) -lreadline -o $(OUT) $(LIBFT)

$(SRC_OBJS): %.o: %.c
	cc $(FLAGS) $(HEADER) -c $< -o $@

clean:
	rm -f $(SRC_OBJS)

fclean: clean
	rm -f $(OUT)

re: fclean all
