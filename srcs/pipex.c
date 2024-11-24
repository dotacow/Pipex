/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/24 20:54:32 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	write_to_pipe(char **argv,char **envp,t_data data)
	// close p_fd[2]
	// opens fd of argv[1] dups it to stdin;
		// protect open and dup
	// dup stdout to p_fd[1]
		// protect dup
	// executes argv[2], takes env from main
		// handle execute fail
	// close p_fd[1], fd free env
{
}

static int read_from_pipe(char **argv,char **envp,t_data data)
// open fd of argv[4] with create and write flags
{
}

int		main(int argc, char **argv, char **envp)
// what to do if cmd1 or/and cmd2 doesn't exist
{
	t_data	data;

	if (argc != 5)
		perror("Invalid usage: ./pipex infile cmd1 cmd2 outfile");
	if (access(argv[1], R_OK) == -1)
		perror("infile error, are you sure it exists?");
	if (pipe(data.p_fd) == -1)
		perror("pipe faliure"); // replace with exit handler
	data.id1 = fork();
	if (data.id1 == -1)
		perror("fork faliure");//add closing  replace with exit handler
	if (data.id1 == 0)
		write_to_pipe(argv, envp, data);// build later, protect?
	else // parent
	{
		data.id2 = fork();
		if (data.id2 == -1)
			perror("fork faliure");//add closing  replace with exit handler
		if (data.id2 == 0)
			read_from_pipe(argv, envp, data);//build later, protect?
	}
	while (wait(NULL));
	return (0);
}

