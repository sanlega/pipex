/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:54:12 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/17 00:31:32 by slegaris         ###   ########.fr       */
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
	flyingfree(args);
	perror("execve");
	exit(errno);
}
