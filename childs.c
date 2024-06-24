/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:54:12 by slegaris          #+#    #+#             */
/*   Updated: 2024/06/24 11:00:29 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int pipefd[2], char *command, int mode, char **env)
{
	char	**args;

	args = esesplit(command, ' ');
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

void	normal_open_fds(int *fds, char *file1, char *file2)
{
	fds[0] = open(file1, O_RDONLY);
	fds[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
