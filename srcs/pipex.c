/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/25 12:57:55 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	write_to_pipe(char **argv,char **envp,t_data data)
// close p_fd[0]
// access(argv[1], R_OK)
	// if failure
	// terminate child.
// open fd of argv[1] | read
	// protect
// link fd to stdin
	// protect
// link p_fd[1] to stdout
	// protect
// ft_execve()
	// close p_fd, fd, free paths
	// throw error
{
}

static int read_from_pipe(char **argv,char **envp,t_data data)
// close p_fd[1]
// access(argv[2], W_OK)
	// if failure
	// terminate child.
// open fd of argv[4] | create | write
	// protect
// lint p_fd[0] to stdin
	// protect
// link fd to stdout
	// protect
// ft_execve()
	// close p_fd, fd, free paths
	// throw error
{
}

int		main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		perror("Invalid usage: ./pipex infile cmd1 cmd2 outfile");
	if (pipe(data.p_fd) == -1)
		perror("pipe faliure"); // replace with exit handler
	data.id1 = fork();
	if (data.id1 == -1)
		perror("fork faliure");//add closing  replace with exit handler
	if (data.id1 == 0)
		write_to_pipe(argv, envp, data);// build later, protect?
	else
	{
		data.id2 = fork();
		if (data.id2 == -1)
			perror("fork faliure");//add closing  replace with exit handler
		if (data.id2 == 0)
			read_from_pipe(argv, envp, data);//build later, protect?
	}
	while (wait(NULL) != -1);
	return (0);
}

