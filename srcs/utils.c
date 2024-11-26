/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:48:16 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/26 14:53:51 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_2d_free (char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{

		free(args[i]);
		i++;
	}
	free(args);
}

char **get_path(char **envp,char *cmd)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		printf("join!\n");
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break;
		}
		i++;
	}
	return (paths);
}

int	ft_execve(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**args;
	char	**paths;

	paths = get_path(envp);
	if (!paths)
		return (-1);
	args = ft_split(cmd, ' ');
	if (!args)
	{
		ft_2d_free(paths);
		return (-1);
	}
	cmd = ft_strjoin("/", args[0]);
	if (!cmd)
	{
		ft_2d_free(paths);
		ft_2d_free(args);
		return (-1);
	}
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (!path)
		{
			perror("path join failure!");
			exit(EXIT_FAILURE); // tbd: exit handler
		}
		if (!access(path,X_OK))
		{
			fprintf(stderr, "%s\n", path);
			execve(path, args, envp);
		}
		i++;
	}
	perror("pipex: cmd not found!");
	ft_2d_free (paths);
	ft_2d_free (args);
	free (cmd);
	return (-1);
}
