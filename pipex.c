/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:44:49 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/26 19:13:33 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "pipex.h"
#include "libft/libft.h"

void	child_process(int pipefd[2], char *command, int mode)
{
	char	**args;

	args = ft_split(command, ' ');
	if (mode == 0)  // modo 0 es productor
		dup2(pipefd[1], STDOUT_FILENO);
	else  // modo 1 es consumidor
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(args[0], args, NULL);
	perror("execve");  // Si execve retorna, error
	exit(1);
}

void	handle_pipe(char *file1, char *command1, char *command2, char *file2)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		fd1;
	int		fd2;

	fd1 = open(file1, O_RDONLY);
	fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("open");
		exit(1);
	}

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0)
	{
		dup2(fd1, STDIN_FILENO);
		child_process(pipefd, command1, 0);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid2 == 0)
	{
		dup2(fd2, STDOUT_FILENO);
		child_process(pipefd, command2, 1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd1);
	close(fd2);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv)
{
	char *error;

	error = "Uso: ./pipex archivo1 comando1 comando2 archivo2";
	if (argc != 5)
	{
		ft_printf("%s\n", error);
		return (1);
	}
	handle_pipe(argv[1], argv[2], argv[3], argv[4]);
	return (0);
}
