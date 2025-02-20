/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:37:15 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/11 14:56:19 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("too many arguments: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

void	new_pwd_oldpwd(t_minishell *t_m, int k)
{
	char	cwd[PATH_MAX];
	char	*temp;

	if (k == 1)
	{
		getcwd(cwd, PATH_MAX);
		temp = ft_strjoin("PWD=", cwd);
		env_lastadd(t_m->env, temp);
		free(temp);
	}
}

static void	update_oldpwd(t_minishell *t_m)
{
	t_env	*old;
	t_env	*pwd;
	char	cwd[PATH_MAX];

	pwd = findenv("PWD", t_m->env);
	old = findenv("OLDPWD", t_m->env);
	if (!pwd)
		new_pwd_oldpwd(t_m, 1);
	else if (!old)
		env_lastadd(t_m->env, "OLDPWD");
	if (old && pwd)
	{
		free(old->val);
		old->val = ft_strdup(pwd->val);
		if (getcwd(cwd, PATH_MAX))
		{
			free(pwd->val);
			pwd->val = ft_strdup(cwd);
		}
	}
}

static int	go_to(int n, t_minishell *t_m)
{
	char	*ev_path;
	t_env	*env;

	ev_path = NULL;
	if (n == 1)
	{
		env = findenv("HOME", t_m->env);
		if (env && env->val)
			ev_path = env->val;
		if (!env)
		{
			update_oldpwd(t_m);
			ft_putendl_fd("minishell : $HOME not set", STDERR);
			t_m->exstat = 1;
			return (ERROR);
		}
	}
	chdir(ev_path);
	update_oldpwd(t_m);
	t_m->exstat = 0;
	return (SUCCESS);
}

int	f__cd(char **args, t_minishell *t_m)
{
	int	cd_return;

	if (ft_tablen(args) > 2)
	{
		t_m->exstat = 1;
		return (ft_putendl_fd("cd: too many arguments", 2), -1);
	}
	if (!args[1])
		return (go_to(1, t_m));
	if (ft_strcmp(args[1], "-") == 0)
		return (go_to(0, t_m));
	else
	{
		cd_return = chdir(args[1]);
		update_oldpwd(t_m);
		if (cd_return != 0)
		{
			print_error(args);
			t_m->exstat = 1;
		}
		else
			t_m->exstat = 0;
	}
	return (cd_return);
}
