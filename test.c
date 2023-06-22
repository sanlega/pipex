/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 03:02:00 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/22 03:22:46 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int fd[2];

	if (pipe(fd) == -1)
		return 1;
	
	int pid1;
	int pid2;

	pid1 = fork();
	if (pid1 < 0)
		return 2;

	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ls", "ls", "-la", NULL);
	}

	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("wc", "wc", "-l", NULL);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	// close(fd[0]);
	// close(fd[1]);
	return (0);
}
