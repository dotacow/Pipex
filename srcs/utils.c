/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:48:16 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/28 19:34:51 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_2d_free(char **args)
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

void	exit_handler(int fd)
{
	perror("ya nashmi! reconsider your life choices (╯°□°）╯︵ ┻━┻.\n");
	if (fd < 0)
		close (fd);
	exit(EXIT_FAILURE);
}

static int	get_env(char **cmd, char ***paths, char **envp)
{
	int	i;

	*cmd = ft_strjoin("/", *cmd);
	if (!*cmd)
		return (0);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			*paths = ft_split(envp[i] + 5, ':');
			if (!*paths)
				return (0);
			break ;
		}
		i++;
	}
	return (1);
}

char	*get_path(char **envp, char *cmd, int i)
{
	char	**paths;
	char	*joined_cmd;
	char	*tmp;

	paths = NULL;
	joined_cmd = NULL;
	if (get_env(&cmd, &paths, envp))
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (!tmp)
			return (NULL);
		if (!access(tmp, X_OK))
		{
			joined_cmd = tmp;
			break ;
		}
		free(tmp);
		i++;
	}
	free(tmp);
	ft_2d_free(paths);
	return (joined_cmd);
}

void	ft_execve(int fd, char *cmd, char **envp)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split(cmd, ' ');
	if (!args)
		exit_handler(fd);
	if (*cmd == 0)
	{
		free(cmd);
		ft_2d_free(args);
		exit_handler(fd);
	}
	cmd = get_path(envp, args[0], i);
	if (!cmd)
	{
		ft_2d_free(args);
		exit_handler(fd);
	}
	execve(cmd, args, envp);
	ft_2d_free(args);
	free(cmd);
	exit_handler(fd);
}
