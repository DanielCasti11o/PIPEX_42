/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:53:29 by dacastil          #+#    #+#             */
/*   Updated: 2025/04/22 16:08:02 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include "../libft_bonus/libft.h"
# include "get_next_line_bonus.h"

// typedef struct s_pid_b
// {
// 	pid_t	*pids;
// 	int		*pipefd[2];
// }	t_pid_b;

typedef struct s_pid
{
	pid_t	pid1;
	int		pipefd[2]; // extremos read & write
}	t_pid;

typedef struct s_pid_b
{
	pid_t	*pids;
	int		(*pipefd)[2]; // extremos read & write
	int		index;
}	t_pid_b;

void	create_process(t_pid *process, char **argv, char **envp);
void	red_input(char *infile, t_pid *process);
void	red_output(char *outfile, t_pid *process);
void	process_command(char **envp, char **argv, int ix_argv);
char	**ft_findpath(char **envp);
char	**split_command(char *arg, char *command);
void	fr_words(char **wds);
void	exec_command(char **r_paths, char **command, char **envp);
char	*creat_path(char	*path, char *argv);
void	ft_error(char *msg, int flag);
char	**process_c(char *command, char *trimm, char *str_arg, char **com_mk);
void	ft_putstr(char *s);

// BONUS

t_pid_b	*init_prh(char **argv, int argc);
void	start_pipe(t_pid_b *process, int n_pipes);
void	destroy_prh(t_pid_b *prh, int n_pipes);
void	red_inputs(char *infile, t_pid_b *process, int i, char **argv);
void	red_output_f(char *outfile, t_pid_b *process, char **argv);
void	create_process_pipes(t_pid_b *process, char **argv, char **envp, int argc);
int		ft_heredoc(char **argv);
void	process_here_doc(t_pid_b *process, char **argv, char **envp, int argc);
void	father_final_heredoc(t_pid_b *process, char **argv, char **env, int argc);
void	father_final(t_pid_b *process, char **argv, char **env, int argc);

#endif
