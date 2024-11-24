/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:55:32 by yokitane          #+#    #+#             */
/*   Updated: 2024/11/24 19:14:10 by yokitane         ###   ########.fr       */
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
	t_data	data;

	if (argc != 5)
		perror("Invalid usage: ./pipex infile cmd1 cmd2 outfile");
	if (access(argv[1], R_OK) == -1)
		perror("infile error, are you sure it exists?");
	if (pipe(data.pipe_fd) == -1)
		perror("pipe faliure"); // replace with exit handler
	data.id1 = fork();
	if (data.id1 == -1)
		perror("fork faliure");//add closing  replace with exit handler
	if (data.id1 == 0)
		child_p1(argv,envp, data);// build later
	else // parent
	{
		data.id2 = fork();
		if (data.id2 == -1)
			perror("fork faliure");//add closing  replace with exit handler
		if (data.id2 == 0)
			child_p2(argv, envp, data);//build later
	}
	wait(NULL); // calling these okay in child
	wait(NULL); // ..........................^
	return (0);
}

