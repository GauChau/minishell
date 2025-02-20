/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:23:33 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/12 13:04:38 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <libft.h>
# include <signal.h>
# include <dirent.h> 
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ERROR 1
# define SUCCESS 0
# define MAX_CMDS 512
# define ERROR 1
# define SUCCESS 0

typedef struct s_gboules
{
	bool	dq;
	bool	sq;
	int		sup;
	int		inf;
	int		other;
	int		space;
	int		pipe;
}	t_gboules;

typedef struct s_files
{
	char			*filename;
	int				is_append;
	bool			is_in;
	bool			is_out;
	bool			is_piped_out;
	bool			is_piped_in;
	bool			is_stdin;
	bool			is_stdout;
	bool			is_heredoc;
	struct s_files	*next;
}	t_files;

typedef struct s_expand
{
	char	*key;
	char	*value;
}	t_expand;

typedef struct s_cmd
{
	t_files	*files;
	char	*prompt;
	char	*command;
	char	*input;
	char	*output;
	int		is_append;
	int		is_piped_out;
	bool	is_piped_in;
	bool	is_stdin;
	bool	is_stdout;
	bool	is_heredoc;
	bool	continue_;
}	t_cmd;

typedef struct s_env
{
	char			*value;
	char			*val;
	char			*key;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	t_env					*env;
	t_cmd					*commands;
	size_t					cmd_count;
	char					**c_args;
	bool					parse_error;
	char					e_v[2];
	pid_t					*pid;
	int						(*pipes_fd)[2];
	int						*heredocs;
	int						exstat;
	int						is_expand;
	int						n_expand;
	int						exp_starter;
	char					**cmdlisttofree;
	char					**nenv;
}	t_minishell;

extern int	g_sigcatch;
/*env*/
char	*get_env(char **env);
char	*get_env_path(t_minishell *t_m);
int		env_init(t_minishell *t_m, char **argv, char *progname);
int		env_lastadd(t_env *t, char *value);
void	display(int argc, t_env **argv);

/*buils*/
int		f__cd(char **args, t_minishell *t_m);
int		f__pwd(int fd_out);
int		f__env(t_env *env, int fdout);
int		f__echo(char **args, int fdout);
int		f__unset(t_minishell *t_m);
void	f__export(t_minishell *t);
int		is_builtin(char *c);
void	run_builtin(t_minishell *t_m, int n_builtin, int fdout, t_cmd *cmd);

/* GAUTIER LE G.O.A.T DU MULTITHREADING */
/*exec*/
void	free_c_args(t_minishell	*t_m);
int		exec_cmds(t_minishell *t_m);
int		child_molestor(t_minishell *t_m, t_cmd *c, size_t i, int c_int);
int		hall_monitor(t_minishell *t_m, size_t i);
int		dupclose(int fd2, int fd1);
int		ft_waiter(t_minishell *t_m);
void	ft_exec2(char *cmd, char **env);
int		open_file(char *file, int n, int append);
char	*bget_path2(char *cmd, char **env);
void	ft_free_tab(char **tab);
int		isspc_only(char *str);
int		error_message(char *path);
int		exec_init(t_minishell *t_m);

/*heredoc*/
int		heredoc(t_minishell *t_m, t_files *flist);
int		heredocalloc(t_minishell *t_m);
int		delete_heredocs(t_minishell *t_m);
int		childhead_handler(t_minishell *t_m, size_t i, t_cmd *c);
char	*tmpnamer(void);

/*ults*/
char	**pipe_env(t_minishell *t_m);
void	f__exit(t_minishell *t_m, t_cmd *c);
char	*rm_quotes(char *s);
int		ft_tablen(char **tab);
void	ft_print_tab(char **tab);
void	shlvlhandler(char **env);
t_env	*findenv(char *name, t_env *env);
int		env_lastadd(t_env *t, char *value);
void	display(int argc, t_env **argv);
int		env_len(t_env *t);
void	sort_env_tab(t_env **tab, int len);
void	filltab(t_env **tab, t_env *env);

/*signals*/
void	signalsetter(int signum, void (*handler)(int));
void	signalignore(int signum);
void	handler(int signum);
void	handler_heredoc(int signum);

/*builtins*/
int		restorefds(t_cmd *c, int fd_stds[2]);
int		openfds(t_minishell *t_m, t_cmd *c, int fd_stds[2], int fd_duped[2]);
int		builtindirector(t_minishell *t_m, t_cmd *c, int n_builtin);
char	**ft_split_quotes(char *s, char c, int remove_quote);
int		arg_check(char *arg);
t_env	*findenv_next(char *name, t_env *env);
t_env	*env_add_void(char *value);

/* gparse */
int		gparse(char *line, t_minishell *t_m);
int		ft_setboules(t_gboules *boules);
int		qt_state(t_gboules *boules, char c);
int		g_prserrors(char *line);
int		ft_char_in_set(char c, char const *set);
void	apply_quote_removal(char **t);
void	free_mesenp(t_minishell *t_m);
void	free_env(t_env *env);
void	free_shit(t_minishell *t_m);
char	*apply_exp(t_minishell *t_m, char *line);
int		ft_update_cmd(t_cmd *cmd, char *line, int head);
char	*exp_tamp(t_minishell *t_m, t_env *env, char *src, int i);

/* FILE MANAGER */
int		ft_addtfile(t_cmd *src, t_files *add);
int		fl_determ(char *line, t_files *sfile);
int		ft_gchau_cparse(t_cmd *cmd, int cmd_count, int i);
int		ft_cmd_creat(char **tab, t_minishell *t_m);
int		ft_fill_cmd(char **tab, t_cmd *c);

#endif
