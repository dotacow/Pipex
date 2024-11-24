/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/24 18:46:40 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void execute(char *cmd, char **env)
{
	char	**paths;
	int		i;

}

int		main(int argc, char **argv, char **envp)
{
	pid_t	id1;
	pid_t	id2;
	int		pipe_fd[2];

	if (argc == 5)
	{
	if (access(argv[1], R_OK | F_OK) == -1)
		perror("infile error, are you sure it exists?");
	if (pipe(pipe_fd) == -1)
		perror("pipe faliure"); // replace with exit handler
	if ((id1 = fork()) == -1)
		perror("fork faliure");//add closing  replace with exit handler
	if (id1 == 0)
		child_p1(argv, envp, pipe_fd, &id1);// build later
	else
	{
		if ((id2 = fork()) == -1)
			perror("fork faliure");//add closing  replace with exit handler
		if (id2 == 0)
			child_p2(argv, envp, pipe_fd, &id2);//build later
	}
	wait(NULL);
	wait(NULL);
	return (0);
	}
}

