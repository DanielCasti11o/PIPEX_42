/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:16:28 by dacastil          #+#    #+#             */
/*   Updated: 2025/03/19 13:53:12 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft_bonus/libft.h"

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

char	**ft_findpath(char **envp)
{
	int		i;
	char	*line;
	char	**wd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5))
			line = (envp[i] + 5); // retorna el string desde la posicion 5
		i++;
	}

	wd = ft_split(line, ':');
	return (wd);
}

char	**split_command(char *arg)
{
	char	**command_mask;
	char	*command;
	char	*str;

	str = ft_strchr(arg, '\'');
	if (!str) // si no tiene 'arg'
	{
		command_mask = ft_split(arg, ' ');
		free(arg);
		return (command_mask);
	}
	else
	{
		command_mask = ft_split(arg, ' ');
		command = command_mask[0];
		fr_words(command_mask);
		command_mask = (char *[]){command, ft_strtrim(str, "'"), NULL};
		free(str);
		free(command);
		return (command_mask);
	}
}
char	*creat_path(char	*path, char *argv)
{
	char	*result;
	char	*base_temp;

	if (ft_strchr(argv, '/')) // Por si viene con ruta
		return (ft_strdup(argv));
	base_temp = ft_strjoin(path, "/"); // base de la ruta
	result = ft_strjoin(base_temp, argv); // la ruta mas el comando, ruta completa
	if (!result)
		return (NULL);
	free(base_temp);
	return(result);
}


void	exec_command(char **rute_paths, char **command_arg, char **argv, int ix)
{
	char	*path;
	int		i;

	i = 0;
	while (rute_paths[i])
	{
		path = creat_path(rute_paths[i], argv[ix]);
		if (access(path, X_OK) == 0)
		{
			execve(path, command_arg, rute_paths);
		}
		free(path);
		i++;
	}

}
