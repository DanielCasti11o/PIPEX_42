/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:26 by dacastil          #+#    #+#             */
/*   Updated: 2025/04/22 16:02:53 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	father_final(t_pid_b *process, char **argv, char **env, int argc)
{
	int	wps;

	wps = 0;
	red_output_f(argv[argc - 1], process, argv);
	process_command(env, argv, (process->index + 2));
	while (process->pids[wps])
	{
		waitpid(process->pids[wps], NULL, 0);
		wps++;
	}
}
void	father_final_heredoc(t_pid_b *process, char **argv, char **env, int argc)
{
	int	wps;

	wps = 0;
	red_output_f(argv[argc - 1], process, argv);
	process_command(env, argv, (process->index + 3));
	while (process->pids[wps])
	{
		waitpid(process->pids[wps], NULL, 0);
		wps++;
	}
}

void	process_here_doc(t_pid_b *process, char **argv, char **envp, int argc)
{
	int	n_pipes;

	process->index = 0;
	n_pipes = argc - 4;
	start_pipe(process, n_pipes);
	while (process->index < n_pipes)
	{
		process->pids[process->index] = fork();
		if (process->pids[process->index] < 0)
		{
			close(process->pipefd[process->index][0]);
			close(process->pipefd[process->index][1]);
			ft_error("ERROR: Fork failed\n", 1);
		}
		else if (process->pids[process->index] == 0)
		{
			red_inputs(argv[process->index], process, process->index, argv);
			process_command(envp, argv, (process->index + 3));
		}
		else if (process->pids[process->index] > 0)
			father_final_heredoc(process, argv, envp, argc);
		process->index++;
	}
	unlink("here_doc_temp");
}

int	ft_heredoc(char **argv)
{
	int		fd_temp;
	char	*line;

		fd_temp = open("here_doc_temp", O_CREAT, O_RDWR, O_TRUNC, 0644);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			{
				free(line);
				break ;
			}
			write(fd_temp, line, ft_strlen(line));
			free(line);
		}
		close(fd_temp);
		return(fd_temp);
}

t_pid_b	*init_prh(char **argv, int argc)
{
	t_pid_b *new;

	new = malloc(sizeof(t_pid_b));
	if (!new)
		return (NULL);
	new->index = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		new->pids = malloc(sizeof(pid_t) * (argc - 4));
	}
	else
		new->pids = malloc(sizeof(pid_t) * (argc - 3));
	if (!new->pids)
		return (free(new), NULL);
	return (new);
}
