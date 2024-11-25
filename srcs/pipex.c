/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/25 16:01:45 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
static int	write_to_pipe(char **argv,char **envp,t_data data)
{
	int	fd;

	close (data.p_fd[0]);
	if (access(argv[1], R_OK) == -1)
	{
		perror("invalid infile!"); //tbd : exit handler
		exit(EXIT_FAILURE);
	}
	fd = open(argv[0],O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE); // tbd : exit handler
	if (dup2(fd, 0) == -1)
		exit(EXIT_FAILURE); // tbd
	if (dup2(data.p_fd[1],1))
		exit(EXIT_FAILURE); // tbd
	ft_execve(argv[2],envp);
	exit(EXIT_FAILURE); // tbd
}
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
static int read_from_pipe(char **argv, char **envp, t_data data)
{
	int	fd;

	close(data.p_fd[1]);
	if (access(argv[4],W_OK) == -1)
		exit(EXIT_FAILURE);
	fd = open(argv[4], O_WRONLY |O_CREAT);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if (dup2(fd, 1) == -1)
		exit(EXIT_FAILURE);
	if (dup2(data.p_fd[0],0) == -1)
		exit(EXIT_FAILURE);
	ft_execve(argv[3],envp);
	exit(EXIT_FAILURE);
}

int		main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		perror("Invalid usage: ./pipex infile cmd1 cmd2 outfile");
	if (pipe(data.p_fd) == -1)
		perror("pipe faliure"); // replace with exit handler
	data.id1 = fork();
	if (!errno)
		perror("fork faliure");//add closing  replace with exit handler
	if (data.id1 == 0)
		write_to_pipe(argv, envp, data);// build later, protect?
	else
	{
		data.id2 = fork();
		if (!errno)
			perror("fork faliure");//add closing  replace with exit handler
		if (data.id2 == 0)
			read_from_pipe(argv, envp, data);//build later, protect?
	}
	while (wait(NULL) != -1);
	return (0);
}

