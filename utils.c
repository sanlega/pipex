/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:32:09 by slegaris          #+#    #+#             */
/*   Updated: 2023/08/15 15:34:23 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int pipefd[2], char *command, int mode)
{
	char	**args;

	args = ft_split(command, ' ');
	if (mode == 0)
		dup2(pipefd[1], STDOUT_FILENO);
	else
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(args[0], args, NULL);
	free(args);
	perror("execve");
	exit(1);
}

void	init_fds(char *file1, char *file2, int *fd1, int *fd2)
{
	*fd1 = open(file1, O_RDONLY);
	*fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd1 < 0 || *fd2 < 0)
	{
		perror("open");
		exit(1);
	}
}

void	init_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

int	process_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}
