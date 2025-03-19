/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:10:22 by dacastil          #+#    #+#             */
/*   Updated: 2025/03/19 14:00:33 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	red_output(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY, 0644);
	if (fd < 0)
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	red_input(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY, 0664);
	if (fd < 0)
		perror("Open failed\n");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	process_command(char **envp, char **argv, int ix_argv)
{
	char	**rute_paths;
	char	**command_arg;

	rute_paths = ft_findpath(envp);
	command_arg = split_command(argv[ix_argv]);
	// for (int i = 0; rute_paths[i]; i++)
	// {
	// 	printf("paths ---> %s\n", rute_paths[i]);
	// 	printf("paths ---> %s\n\n", command_arg[i]);
	// }
	exec_command(rute_paths, command_arg, argv, ix_argv);
}

void	create_process(t_pid process, char **argv, char **envp)
{
	process.pid1 = fork();
	if (process.pid1 < 0)
		perror("Fork failed\n");
	else if (process.pid1 == 0)
	{
		red_input(argv[1]);
		close(process.pipefd[0]);
		dup2(process.pipefd[1], STDOUT_FILENO);
		close(process.pipefd[1]);
		process_command(envp, argv, 2);
	}
	process.pid2 = fork();
	if (process.pid2 < 0)
		perror("Fork failed\n");
	else if (process.pid2 == 0)
	{
		red_output(argv[4]);
		close(process.pipefd[1]);
		dup2(process.pipefd[0], STDIN_FILENO);
		close(process.pipefd[0]);
		process_command(envp, argv, 3);
	}
	close(process.pipefd[0]);
	close(process.pipefd[1]);
	printf("OK\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_pid	process; // proceso 1
	// int	i;

	// i = 0;
	// while (envp[i])
	// {
	// 	printf("linea x = %s\n", envp[i]);
	// 	i++;
	// }
	if ((argc - 1) != 4)
		perror("Invalid Arguments\n");
	if ((pipe(process.pipefd)) < 0)
		perror("Pipe failed");
	create_process(process, argv, envp);
	waitpid(process.pid1, NULL, 0);
	waitpid(process.pid2, NULL, 0);
}
