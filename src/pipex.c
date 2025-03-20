/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:10:22 by dacastil          #+#    #+#             */
/*   Updated: 2025/03/20 16:26:26 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	red_output(char *outfile, t_pid *process)
{
	int	fd;

	close(process->pipefd[1]);
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		close(process->pipefd[0]);
		ft_error("Failed\n", 1);
	}
	if (dup2(process->pipefd[0], STDIN_FILENO) < 0
		|| dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		close(process->pipefd[0]);
		ft_error("ERROR: DUP2\n", 1);

	}
	close(process->pipefd[0]);
	close(fd);
}

void	red_input(char *infile, t_pid *process)
{
	int	fd;

	close(process->pipefd[0]);
	fd = open(infile, O_RDONLY, 0664);
	if (fd < 0)
	{
		close(process->pipefd[1]);
		ft_error("Open failed\n", 1);
	}
	if (dup2(fd, STDIN_FILENO) < 0
		|| dup2(process->pipefd[1], STDOUT_FILENO) < 0)
	{
		close(fd);
		close(process->pipefd[1]);
		ft_error("ERROR: DUP2\n", 1);

	}
	close(fd);
	close(process->pipefd[1]);
}

void	process_command(char **envp, char **argv, int ix_argv)
{
	char	**rute_paths;
	char	**command_arg;
	char	*command;

	command = NULL;
	if (!ft_strchr(argv[ix_argv], '/'))
	{
		rute_paths = ft_findpath(envp);
		if (!rute_paths)
			ft_error("Error: envp\n", 1);
		if (ft_strlen(argv[ix_argv]) == 0)
		{
			fr_words(rute_paths);
			ft_error("Error: Invalid Command\n", 1);
		}
	}
	command_arg = split_command(argv[ix_argv], command);
	if (!command_arg)
		return (fr_words(envp), fr_words(argv),
			ft_error("ERROR: command\n", 1));
	if (!ft_strchr(argv[ix_argv], '/'))
		exec_command(rute_paths, command_arg, envp);
	else
		exec_command(command_arg, command_arg, envp);
}

// for (int i = 0; rute_paths[i]; i++)
// {
// 	printf("paths ---> %s\n", rute_paths[i]);
// 	printf("paths ---> %s\n\n", command_arg[i]);
// }

void	create_process(t_pid *process, char **argv, char **envp)
{
	process->pid1 = fork();
	if (process->pid1 < 0)
	{
		close(process->pipefd[0]);
		close(process->pipefd[1]);
		ft_error("Fork failed\n", 1);
	}
	else if (process->pid1 == 0)
	{
		red_input(argv[1], process);
		process_command(envp, argv, 2);
	}
	waitpid(process->pid1, NULL, 0);
	red_output(argv[4], process);
	process_command(envp, argv, 3);
}

int	main(int argc, char **argv, char **envp)
{
	t_pid	process;

	if ((argc - 1) != 4)
		ft_error("Invalid Arguments\n", 1);
	if (pipe(process.pipefd) < 0)
		ft_error("Pipe failed\n", 1);
	create_process(&process, argv, envp);
	return (0);
}
