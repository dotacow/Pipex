/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:30:31 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/25 15:40:24 by yokitane         ###   ########.fr       */
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

char	**get_path(char **envp);
int		ft_execve(char *cmd, char **envp);

#endif