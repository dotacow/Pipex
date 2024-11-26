/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/26 14:10:41 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	write_to_pipe(char **argv,char **envp,t_data *data1)
{
	int	fd;
	t_data data = *data1;

	fprintf(stderr, "hi from first child");
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
	close(data.p_fd[1]);
	close(fd);
	ft_execve(argv[2],envp);
	exit(EXIT_FAILURE); // tbd
}

static int read_from_pipe(char **argv, char **envp, t_data *data1)
{
	int	fd;
	t_data data = *data1;
	// printf("exec from second child");

	close(data.p_fd[1]);
	fd = open(argv[4], O_WRONLY | O_CREAT, 00400 | 00200);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if (dup2(fd, 1) == -1)
		exit(EXIT_FAILURE);
	if (dup2(data.p_fd[0], 0) == -1)
		exit(EXIT_FAILURE);
	fprintf(stderr, "exec from second child");
	close(data.p_fd[0]);
	close(fd);
	ft_execve(argv[3], envp);
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
	close(data.p_fd[0]);
	close(data.p_fd[1]);
	while (wait(NULL) != -1);
	return (0);
}
