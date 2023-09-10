/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:32:09 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/10 19:33:21 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int pipefd[2], char *command, int mode, char **env)
{
	char	**args;

	args = ft_split(command, ' ');
	if (mode == 0)
		dup2(pipefd[1], STDOUT_FILENO);
	else
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(args[0], args, env);
	free(args);
	perror("execve");
	exit(errno);
}

void	init_fds(char *file1, char *file2, int *fds)
{
	fds[0] = open(file1, O_RDONLY);
	fds[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[0] < 0 || fds[1] < 0)
	{
		perror("open");
		exit(errno);
	}
}

void	init_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(errno);
	}
}

int	process_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(errno);
	}
	return (pid);
}

void	dotcomma_error(char *cmd)
{
	perror(cmd);
	exit(errno);
}
