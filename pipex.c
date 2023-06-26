/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:44:49 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/26 20:10:21 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "pipex.h"
#include "libft/libft.h"

void	ft_child_process(int pipefd[2], char *command, int mode)
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

void ft_init_fds(char *file1, char *file2, int *fd1, int *fd2)
{
	*fd1 = open(file1, O_RDONLY);
	*fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd1 < 0 || *fd2 < 0)
	{
		perror("open");
		exit(1);
	}
}

void ft_init_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

int ft_process_fork()
{
	int pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return pid;
}

void ft_handle_child_process(int fd, int *pipefd, char *command, int mode)
{
	if (mode)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	ft_child_process(pipefd, command, mode);
}

void ft_handle_parent_process(int *pipefd, int fd1, int fd2, int pid1, int pid2)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd1);
	close(fd2);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void ft_execute_child_process(int fd, int *pipefd, char *command, int mode, char **envp)
{
	char    *cmd_path;

	cmd_path = ft_get_command_path(envp, command);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(1);
	}

	if (mode)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	ft_child_process(pipefd, cmd_path, mode);

	free(cmd_path);
}

void ft_handle_pipe(char *file1, char *command1, char *command2, char *file2, char **envp)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		fd1;
	int		fd2;

	ft_init_fds(file1, file2, &fd1, &fd2);
	ft_init_pipe(pipefd);

	pid1 = ft_process_fork();
	if (pid1 == 0)
		ft_execute_child_process(fd1, pipefd, command1, 0, envp);

	pid2 = ft_process_fork();
	if (pid2 == 0)
		ft_execute_child_process(fd2, pipefd, command2, 1, envp);

	ft_handle_parent_process(pipefd, fd1, fd2, pid1, pid2);
}

int	main(int argc, char **argv, char **envp)
{
	char *error;

	error = "Uso: ./pipex archivo1 comando1 comando2 archivo2";
	if (argc != 5)
	{
		ft_printf("%s\n", error);
		return (1);
	}
	ft_handle_pipe(argv[1], argv[2], argv[3], argv[4], envp);
	return (0);
}
