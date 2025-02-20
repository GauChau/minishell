/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:04:00 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 18:18:02 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tmpnamer(void)
{
	size_t	i;
	char	*res;

	i = 0;
	while (i < 999999)
	{
		res = ft_itoa(i);
		if (access(res, F_OK))
			break ;
		else
			free(res);
		i++;
	}
	return (res);
}

int	here_err(char *line, int *exs)
{
	if (g_sigcatch)
	{
		(*exs) = 130;
		return (0);
	}
	if (!line)
	{
		(*exs) = 0;
		ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
		return (0);
	}
	return (1);
}

int	here_writer2(t_minishell *t_m, char *eof, int docfd, char *line)
{
	if (line)
	{
		line = apply_exp(t_m, line);
		if (ft_strlen(eof) == ft_strlen(line))
		{
			if (!ft_strncmp(eof, line, ft_strlen(eof)))
				return (0);
		}
		ft_putendl_fd(line, docfd);
		free(line);
	}
	return (1);
}

int	heredoc_writer(t_minishell *t_m, char *eof, char *tempfile)
{
	char	*line;
	int		docfd;
	int		fdstd;
	int		exs;

	fdstd = dup(0);
	exs = 0;
	signalsetter(SIGINT, handler_heredoc);
	docfd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 777);
	if (docfd == -1)
		return (perror("openheredoc err: "), -1);
	while (1)
	{
		line = readline("heredoc>");
		if (!here_err(line, &exs))
			break ;
		if (!here_writer2(t_m, eof, docfd, line))
			break ;
	}
	if (line)
		free(line);
	return (dup2(fdstd, 0), close(fdstd), close(docfd), exit(exs), 1);
}

int	heredoc(t_minishell *t_m, t_files *flist)
{
	char	*tempfile;
	pid_t	pid;

	tempfile = tmpnamer();
	if (!tempfile)
		return (perror("join err: "), -1);
	signalignore(SIGINT);
	pid = fork();
	if (!pid)
		heredoc_writer(t_m,
			apply_exp(t_m, rm_quotes(flist->filename)), tempfile);
	if (pid)
		waitpid(pid, &t_m->exstat, 0);
	signalsetter(SIGINT, handler);
	if (t_m->exstat)
		return (free(flist->filename), flist->filename = tempfile, -1);
	free(flist->filename);
	flist->filename = tempfile;
	return (3);
}
