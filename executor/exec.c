/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:08:14 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/11 18:38:22 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec2(char *cmd, char **env)
{
	char	**ft_cmd;
	char	*path;
	int		k;

	if (cmd[0] == '\0' || !isspc_only(rm_quotes(cmd)))
		exit(0);
	ft_cmd = ft_split_quotes(cmd, ' ', 0);
	path = bget_path2(ft_cmd[0], env);
	apply_quote_removal(ft_cmd);
	if (execve(path, ft_cmd, env) == -1)
	{
		k = error_message(cmd);
		ft_free_tab(ft_cmd);
		exit(k);
	}
}

int	ft_soloexec(t_minishell *t_m, size_t i, int c_int)
{
	t_cmd	*c;

	c = &(t_m->commands[i]);
	t_m->exp_starter = -1;
	t_m->nenv = pipe_env(t_m);
	if (i < t_m->cmd_count)
		if (pipe(t_m->pipes_fd[i]) == -1)
			return (-1);
	signalignore(SIGINT);
	t_m->pid[i] = fork();
	if (t_m->pid[i] == -1)
		return (-1);
	if (!t_m->pid[i])
		child_molestor(t_m, c, i, c_int);
	else
		hall_monitor(t_m, i);
	free(t_m->nenv);
	return (1);
}

int	updt_lst_prog(char **args, t_minishell *t_m)
{
	int		i;
	t_env	*env;

	env = t_m->env;
	i = ft_tablen(args);
	if (i - 1 >= 0)
	{
		env = (findenv("_", t_m->env));
		if (env)
		{
			free(env->val);
			env->val = ft_strdup(args[i - 1]);
		}
	}
	return (0);
}

int	executions(t_minishell *t_m, size_t i)
{
	t_cmd	*c;
	int		c_int;

	c = &(t_m->commands[i]);
	if (ft_strlen(c->command) < 1)
		ft_soloexec(t_m, i, -1);
	else
	{
		c->command = apply_exp(t_m, c->command);
		t_m->c_args = ft_split_quotes(c->command, ' ', 1);
		updt_lst_prog(t_m->c_args, t_m);
		c_int = is_builtin(rm_quotes(t_m->c_args[0]));
		if (c_int != -1 && t_m->cmd_count == 1)
			builtindirector(t_m, c, c_int);
		else
			ft_soloexec(t_m, i, c_int);
		ft_free_tab(t_m->c_args);
	}
	return (0);
}

int	exec_cmds(t_minishell *t_m)
{
	size_t	i;

	i = 0;
	if (exec_init(t_m) == -1)
		return (-1);
	if (heredocalloc(t_m) != -1)
		while (i < t_m->cmd_count)
			executions(t_m, i++);
	else
		write(2, "\n", 1);
	if (t_m->exp_starter == -1)
		ft_waiter(t_m);
	delete_heredocs(t_m);
	signalsetter(SIGINT, handler);
	free(t_m->pid);
	t_m->pid = NULL;
	free(t_m->pipes_fd);
	t_m->pipes_fd = NULL;
	return (0);
}
