/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:16:28 by dacastil          #+#    #+#             */
/*   Updated: 2025/03/20 16:45:03 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft_bonus/libft.h"

char	**ft_findpath(char **envp)
{
	int		i;
	char	**wd;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
	{
		i++;
	}
	wd = ft_split((envp[i] + 5), ':');
	if (!wd)
		return (NULL);
	return (wd);
}

char	**process_c(char *command, char *trimm)
{
	char	**command_mask;

	command_mask = malloc(3 * sizeof(char *));
	if (!command_mask)
		return (NULL);
	command_mask[0] = command;
	command_mask[1] = trimm;
	command_mask[2] = NULL;
	return (command_mask);
}


char	**split_command(char *arg, char *command)
{
	char	**command_mask;
	char	*str_arg;
	char	*trimm;

	str_arg = ft_strchr(arg, 39);
	if (!str_arg)
	{
		command_mask = ft_split(arg, ' ');
		if (!command_mask)
			return (free(str_arg), ft_error("Command invalid\n", 1), NULL);
		return (command_mask);
	}
	else
	{
		command_mask = ft_split(arg, ' ');
		command = ft_strdup(command_mask[0]);
		trimm = ft_strtrim(str_arg, "'");
		if (!trimm)
			return (free(str_arg), NULL);
		fr_words(command_mask);
		command_mask = process_c(command, trimm);
		if (!command_mask)
			return (free(command), free(trimm), NULL);
		return (command_mask);
	}
}

char	*creat_path(char	*path, char *argv)
{
	char	*result;
	char	*base_temp;

	if (ft_strchr(argv, '\''))
		return (ft_strdup(argv));
	base_temp = ft_strjoin(path, "/");
	if (!base_temp)
		return (NULL);
	result = ft_strjoin(base_temp, argv);
	if (!result)
		return (free(base_temp), NULL);
	free(base_temp);
	return (result);
}


void	exec_command(char **r_paths, char **command, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (r_paths[i])
	{
		path = creat_path(r_paths[i], command[0]);
		if (!path)
			return (fr_words(r_paths), fr_words(command),
				fr_words(envp), ft_error("ERROR: path\n", 1));
		if (access(path, X_OK) == 0)
		{
			execve(path, command, envp);
		}
		free(path);
		i++;
	}
	if (r_paths)
		fr_words(r_paths);
	fr_words(command);
	ft_error("Invalid command\n", 1);
}
