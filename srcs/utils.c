/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:48:16 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/27 17:49:22 by yokitane         ###   ########.fr       */
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

void	exit_handler(t_data *data)
{
	perror("reconsider your life choices.\n");
	while (wait(NULL) > 0);
	close(data->p_fd[0]);
	close(data->p_fd[1]);
	exit(EXIT_FAILURE);
}

static void	get_env(char **cmd, char ***paths, char **envp)
{
	int	i;

	*cmd = ft_strjoin("/", *cmd);
	if (!*cmd)
		return ;
	*paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			*paths = ft_split(envp[i] + 5, ':');
			if (!*paths)
				exit(EXIT_FAILURE);
			break ;
		}
		i++;
	}
}

char	*get_path(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*joined_cmd;
	char	*tmp;

	paths = NULL;
	joined_cmd = NULL;
	get_env(&cmd, &paths, envp);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (!cmd)
			return (NULL);
		if (!access(tmp, X_OK))
		{
			joined_cmd = tmp;
			break ;
		}
		i++;
	}
	ft_2d_free(paths);
	return (joined_cmd);
}

int	ft_execve(int fd, char *cmd, char **envp)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		return (-1);
	if (*cmd == 0)
		return (-1);
	cmd = get_path(envp, args[0]);
	if (!cmd)
		return (-1);
	// fprintf(stderr,"%s\n",cmd);
	execve(cmd, args, envp);
	ft_2d_free(args);
	free(cmd);
	close (fd);
	return (-1);
}
