/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:48:16 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/25 09:28:11 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char **get_path(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break;
		}
		i++;
	}
	if (paths == NULL)
	{
		perror("path retrieval failure!");
		exit(EXIT_FAILURE); // tbd: exit handler
	}
	return (paths);
}

int	ft_execve(char *cmd, char **paths, char **envp)
{
	int		i;
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		perror("cmd split failure!");
		exit(EXIT_FAILURE); // tbd: exit handler, return -1, free paths and close fd in main
	}
	cmd = ft_strjoin2("/", cmd);
	if (!cmd)
	{
		perror("cmd join failure!");
		exit(EXIT_FAILURE); // tbd: exit handler, free args ...^
	}
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin2(paths[i], cmd);
		if (!path)
		{
			perror("path join failure!");
			exit(EXIT_FAILURE); // tbd: exit handler
		}
		if (execve(path, args, envp) == -1)
			i++;
	}
	perror("pipex: cmd not found!");
	exit(EXIT_FAILURE); // tbd: exit handler, return --1 free args, path, paths, close fd in main

}
