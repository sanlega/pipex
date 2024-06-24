/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:32:09 by slegaris          #+#    #+#             */
/*   Updated: 2024/06/24 11:00:13 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_fds(char *file1, char *file2, int *fds, char **av)
{
	char	*line;

	if (BONUS == 1)
	{
		fds[0] = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
		while (1)
		{
			ft_printf("HERE_DOC>> ");
			line = get_next_line(0);
			if ((ft_strncmp(line, av[2], ft_strlen(av[2])) == 0
					&& ft_strlen(line) - 1 == ft_strlen(av[2])) || line == NULL)
			{
				if (line != NULL)
					free(line);
				break ;
			}
			ft_putstr_fd(line, fds[0]);
			free(line);
		}
		close(fds[0]);
		fds[0] = open(".heredoc", O_RDONLY);
		fds[1] = open(av[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
		normal_open_fds(fds, file1, file2);
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
