/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:10:22 by dacastil          #+#    #+#             */
/*   Updated: 2025/03/18 18:22:09 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	red_output(t_pid process)
{
	int	fd;

	fd = open("../outfile.txt", O_WRONLY, 0644);
	if (fd < 0)
	{
		fd = open("../outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	red_input(t_pid process)
{
	int	fd;

	fd = open("../input_file.txt", O_RDONLY, 0664);
	if (fd < 0)
		perror("Open failed\n");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	create_process(t_pid process, char **argv, char **envp)
{
	process.pid1 = fork();
	if (process.pid1 < 0)
		perror("Fork failed\n");
	else if (process.pid1 == 0)
	{
		red_input(process);
		close(process.pipefd[0]);
		dup2(process.pipefd[1], STDOUT_FILENO);
		close(process.pipefd[1]);
		execve(ft_findpath(), separate(argv), separateenvp(envp))
	}
	process.pid2 = fork();
	if (process.pid2 < 0)
		perror("Fork failed\n");
	else if (process.pid2 == 0)
	{
		red_output(process);
		close(process.pipefd[1]);
		dup2(process.pipefd[0], STDIN_FILENO);
		close(process.pipefd[0]);
		execlp("wc", "wc", "-l", NULL);
	}
	close(process.pipefd[0]);
	close(process.pipefd[1]);
	printf("OK\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_pid	process; // proceso 1

	if ((argc - 1) != 4)
		perror("Invalid Arguments\n");
	if ((pipe(process.pipefd)) < 0)
		perror("Pipe failed");
	create_process(process, argv, envp);
	waitpid(process.pid1, NULL, 0);
	waitpid(process.pid2, NULL, 0);
}
