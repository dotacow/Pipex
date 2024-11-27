/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:30:31 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/27 14:41:16 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_data
{
	pid_t	id1;
	pid_t	id2;
	int		p_fd[2];
}	t_data;

char	*get_path(char **envp, char *cmd);
int		ft_execve(char *cmd, char **envp);
void	exit_handler(t_data *data);

#endif