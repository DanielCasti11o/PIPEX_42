/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:53:00 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/22 16:08:27 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	destroy_prh(t_pid_b *prh, int n_pipes)
{
	int	i;

	i = 0;
	prh->index = 0;
	if (prh->pids)
		free(prh->pids);
	while (i < n_pipes)
	{
		close(prh->pipefd[i][0]);
		close(prh->pipefd[i][1]);
		free(prh->pipefd[i]);
		i++;
	}
	free(prh->pipefd);
	free(prh);
}

void	start_pipe(t_pid_b *process, int n_pipes)
{
	int	i;

	i = 0;
	process->pipefd = malloc(sizeof(int[2]) * n_pipes);
	while (i < n_pipes)
	{
	if (pipe(process->pipefd[i]) < 0)
		{
			destroy_prh(process, n_pipes);
			ft_error("ERROR: Pipe failed\n", 1);
		}
		i++;
	}
}
#include <errno.h>

void	ft_error(char *msg, int flag)
{
	ft_putstr(msg);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(flag);
}

void	fr_words(char **wds)
{
	int	i;

	i = 0;
	while (wds[i])
	{
		free(wds[i]);
		i++;
	}
	free(wds);
}

void	ft_putstr(char *s)
{
	int	ln;

	ln = 0;
	if (!s)
		s = "(null)";
	while (s[ln])
	{
		write (1, &s[ln], 1);
		ln++;
	}
	return ;
}
