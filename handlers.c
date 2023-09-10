/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:53:40 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/10 20:08:23 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_parent_process(int *pipefd, int *fds, int pid1, int pid2)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
