/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:48:16 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/26 19:07:40 by yokitane         ###   ########.fr       */
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

char *get_path(char **envp,char *cmd)
{
	int		i;
	char	**paths;
	char	*joined_cmd;
	char	*tmp;

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
	cmd = ft_strjoin("/", cmd);
	joined_cmd = NULL;
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i],cmd);
		fprintf(stderr,"%s\n",tmp);
		if (!cmd)
			return (NULL);
		if (!access(tmp,X_OK))
		{
			joined_cmd = tmp;
			break;
		}
		i++;
	}
	ft_2d_free(paths);
	return (joined_cmd);
}

int	ft_execve(char *cmd, char **envp)
{
	char	**args;

	args = ft_split(cmd,' ');
	if (!args)
		return (-1);
	cmd = get_path(envp, args[0]);
	if (!cmd)
		return (-1);
	fprintf(stderr, "%s\n", cmd);
	fprintf(stderr, "%s\n", args[0]);
	execve(cmd,args,envp);
	return (-1);

}
