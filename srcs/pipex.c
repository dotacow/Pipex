/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/12/11 19:29:41 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	exit_pipe(t_data *data)
{
	if (data->p_fd[0] > 0)
		close(data->p_fd[0]);
	if (data->p_fd[1] > 0)
		close(data->p_fd[1]);
	perror("ya nashmi! reconsider your life choices (╯°□°）╯︵ ┻━┻.\n");
	exit(EXIT_FAILURE);
}

static void	write_to_pipe(char **argv, char **envp, t_data *data)
{
	int	fd;

	close(data->p_fd[0]);
	if (access(argv[1], R_OK) == -1)
		exit_handler(data->p_fd[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_handler(data->p_fd[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (errno)
		exit_handler(data->p_fd[1]);
	dup2(data->p_fd[1], STDOUT_FILENO);
	close(data->p_fd[1]);
	if (errno)
		exit_handler(-1);
	ft_execve(fd, argv[2], envp);
	exit_handler(-1);
}

static void	read_from_pipe(char **argv, char **envp, t_data *data)
{
	int	fd;

	close(data->p_fd[1]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00400 | 00200);
	if (fd < 0)
		exit_handler(data->p_fd[0]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (errno)
		exit_handler(data->p_fd[0]);
	dup2(data->p_fd[0], STDIN_FILENO);
	close(data->p_fd[0]);
	if (errno)
		exit_handler(data->p_fd[0]);
	ft_execve(fd, argv[3], envp);
	exit_handler(-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		exit_handler(-1);
	if (pipe(data.p_fd) == -1)
		exit_handler(-1);
	data.id1 = fork();//
	if (errno)
		exit_pipe(&data);
	if (!data.id1)
		write_to_pipe(argv, envp, &data);
	if (data.id1)
	{
		data.id2 = fork();
		if (errno)
			exit_pipe(&data);
		if (!data.id2)
			read_from_pipe(argv, envp, &data);
	}
	close(data.p_fd[0]);
	close(data.p_fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
