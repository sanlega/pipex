/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:13:41 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/26 23:18:05 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_close_pipes(int *pipefd)
{
    close (pipefd[0]);
    close (pipefd[1]);
}

void    ft_close_fd(int fd1, int fd2)
{
    close (fd1);
    close (fd2);
}

void    ft_wait_pids(int pid1, int pid2)
{
    waitpid (pid1, NULL, 0);
    waitpid (pid2, NULL, 0);
}
