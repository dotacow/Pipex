/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/25 21:04:41 by yokitane         ###   ########.fr       */
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
static int	write_to_pipe(char **argv,char **envp,t_data *data1)
{
	int	fd;
	t_data data = *data1;

	close(data.p_fd[0]);
	if (access(argv[1], R_OK) == -1)
	{
		perror("invalid infile!"); //tbd : exit handler
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1],O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE); // tbd : exit handler
	if (dup2(fd, 0) == -1)
		exit(EXIT_FAILURE); // tbd
	if (dup2(data.p_fd[1],1))
		exit(EXIT_FAILURE); // tbd
	ft_execve(argv[2],envp);
	close(data.p_fd[1]);
	close(fd);
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
static int read_from_pipe(char **argv, char **envp, t_data *data1)
{
	int	fd;
	t_data data = *data1;

	close(data.p_fd[1]);
	if (access(argv[4],W_OK) == -1)
		exit(EXIT_FAILURE);
	fd = open(argv[4], O_WRONLY |O_CREAT);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if (dup2(fd, 1) == -1)
		exit(EXIT_FAILURE);
	if (dup2(data.p_fd[0], 0) == -1)
		exit(EXIT_FAILURE);
	ft_execve(argv[3], envp);
	close(data.p_fd[0]);
	close(fd);
	exit(EXIT_FAILURE);
}
// potential bonus: fork in write/read pipe, allowing to use multiple pipes
int		main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		perror("Invalid usage: ./pipex infile cmd1 cmd2 outfile");
		exit(EXIT_FAILURE);
	}
	if (pipe(data.p_fd) == -1)
		return (2);
	data.id1 = fork();
	if (data.id1 == -1)
		return (3);
	if (data.id1 == 0)
		write_to_pipe(argv, envp, &data);
	if (data.id1 > 0)
	{
		data.id2 = fork();
		if (data.id2 == -1)
			perror("fork faliure");//add closing  replace with exit handler
		if (data.id2 == 0)
			read_from_pipe(argv, envp, &data);//build later, protect?
	}
	while (wait(NULL) != -1);
	return (0);
}
