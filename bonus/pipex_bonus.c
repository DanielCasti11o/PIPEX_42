/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:19:27 by dacastil          #+#    #+#             */
/*   Updated: 2025/04/22 16:07:31 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	red_output_f(char *outfile, t_pid_b *process, char **argv)
{
	int	fd;

	close(process->pipefd[process->index][1]);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		close(process->pipefd[process->index][0]);
		ft_error("ERROR: Open Failed\n", 1);
	}
	if (dup2(process->pipefd[process->index][0], STDIN_FILENO) < 0
		|| dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		close(process->pipefd[process->index][0]);
		ft_error("ERROR: DUP2\n", 1);

	}
	close(process->pipefd[process->index][0]);
	close(fd);
}

void	red_inputs(char *infile, t_pid_b *process, int i, char **argv)
{
	int	fd;

	close(process->pipefd[i][0]);
	if (ft_strncmp(infile, "here_doc", 8) == 0)
		fd = ft_heredoc(argv);
	else
		fd = open(infile, O_RDONLY, 0664);
	if (fd < 0)
	{
		close(process->pipefd[i][1]);
		ft_error("ERROR: Open failed\n", 1);
	}
	if (i != 0)
		dup2(process->pipefd[i - 1][0], STDIN_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	if (dup2(process->pipefd[i][1], STDOUT_FILENO) < 0)
	{
		close(fd);
		close(process->pipefd[i][1]);
		ft_error("ERROR: DUP2\n", 1);
	}
	close(fd);
	close(process->pipefd[i][1]);
}

void	process_command(char **envp, char **argv, int ix_argv)
{
	char	**rute_paths;
	char	**command_arg;
	char	*command;

	command = NULL;
	rute_paths = NULL;
	if (!ft_strchr(argv[ix_argv], '/'))
	{
		rute_paths = ft_findpath(envp);
		if (ft_strlen(argv[ix_argv]) == 0)
			return (fr_words(rute_paths),
				ft_error("Error: Invalid Command\n", 1));
		if (!rute_paths)
			ft_error("Error: envp\n", 1);
	}
	command_arg = split_command(argv[ix_argv], command);
	if (!command_arg)
		ft_error("ERROR: command\n", 1);
	if (!ft_strchr(argv[ix_argv], '/'))
		exec_command(rute_paths, command_arg, envp);
	else
	{
		if (execve(argv[ix_argv], command_arg, envp) == -1)
			return (fr_words(command_arg), ft_error("ERROR: command\n", 1));
	}
}

void	create_process_pipes(t_pid_b *process, char **argv, char **envp, int argc)
{
	int	n_pipes;

	process->index = 0;
	n_pipes = argc - 3;
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
			process_command(envp, argv, (process->index + 2));
		}
		else if (process->pids[process->index] > 0)
			father_final(process, argv, envp, argc);
		process->index++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pid_b	*process;

	process = init_prh(argv, argc); // aqui hago la reserva de memoria
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			destroy_prh(process, argc - 4);
			ft_error ("For here_doc is necesary 6 args!\n", 1);
		}
		process_here_doc(process, argv, envp, argc); // aqui entra a la funcion que te mostre
	}
	else
	{
		if (argc < 5)
		{
			destroy_prh(process, argc - 3);
			ft_error("ERROR: Invalid Arguments Format! \n", 1);
		}
	}
	create_process_pipes(process, argv, envp, argc);
	return (0);
}

