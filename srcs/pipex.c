/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/26 18:44:14 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	write_to_pipe(char **argv,char **envp,t_data *data1)
// protectioooooooooooooons!!!!!!!!!1
{
	int	fd;
	t_data data;

	data = *data1;
	close(data.p_fd[0]);
	if (access(argv[1], R_OK) == -1)
	{
		perror("invalid infile!"); //tbd : exit handler
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1],O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(data.p_fd[1], STDOUT_FILENO);
	close(data.p_fd[1]);
	ft_execve(argv[2],envp);
	return(-1);
}

static int read_from_pipe(char **argv, char **envp, t_data *data1)
// protectioooooooooooooons!!!!!!!!!1
{
	int	fd;
	t_data data = *data1;

	close(data.p_fd[1]);
	fd = open(argv[4], O_WRONLY | O_CREAT, 00400 | 00200);
	dup2(fd,STDOUT_FILENO);
	close(fd);
	dup2(data.p_fd[0],STDIN_FILENO);
	close(data.p_fd[0]);
	ft_execve(argv[3], envp);
	return(-1);
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
