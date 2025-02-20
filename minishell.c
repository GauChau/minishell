/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:07:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/12 12:43:29 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_sigcatch = 0;

void	minishell(t_minishell *t_m)
{
	char	*line;

	signalignore(SIGQUIT);
	signalsetter(SIGINT, handler);
	t_m->is_expand = 0;
	t_m->exp_starter = 0;
	t_m->exstat = 0;
	while (1)
	{
		line = readline("slayshell$ ");
		if (line == NULL)
			break ;
		add_history(line);
		if (ft_strlen(line) < 1 || g_prserrors(line) == -1)
			free(line);
		else
		{
			gparse(line, t_m);
			exec_cmds(t_m);
			free_mesenp(t_m);
			free(line);
		}
	}
}

char	**envnull(char	*argname)
{
	char	**env;
	char	cwd[PATH_MAX];

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		return (NULL);
	if (!getcwd(cwd, PATH_MAX))
		cwd[0] = '\0';
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strdup("SHLVL=0");
	env[2] = ft_strjoin("_=", argname);
	env[3] = NULL;
	return (env);
}

int	main(int argc, char **argv, char **env)
{	
	t_minishell	*t_m;

	(void)argv;
	if (!env || argc > 1)
		return (0);
	if (!*env)
		env = envnull(argv[0]);
	shlvlhandler(env);
	t_m = ft_calloc(1, sizeof(t_minishell));
	if (!t_m)
		return (EXIT_FAILURE);
	env_init(t_m, env, argv[0]);
	minishell(t_m);
	free_mesenp(t_m);
	free_shit(t_m);
	free_env(t_m->env);
	free(t_m);
	write(2, "exit\n", 5);
	exit(EXIT_SUCCESS);
}
