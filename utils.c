/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:32:09 by slegaris          #+#    #+#             */
/*   Updated: 2024/06/18 22:09:56 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_fds(char *file1, char *file2, int *fds)
{
    /* if (BONUS = 1) */
    /* { */
    /*     str = get_next_line(0) */
    /*     doc */
    /* } */
	fds[0] = open(file1, O_RDONLY);
	fds[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

int	no_access(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		perror(cmd);
		exit(errno);
	}
	return (1);
}
