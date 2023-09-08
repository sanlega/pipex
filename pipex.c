/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:44:49 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/08 07:24:42 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_child_process(int fd, int *pipefd, char *command, int mode, char **env)
{
	if (mode)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	child_process(pipefd, command, mode, env);
}

void	handle_parent_process(int *pipefd, int fd1, int fd2, int pid1, int pid2)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd1);
	close(fd2);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	execute_child_process(int fd, int *pipefd, char *command, int mode, char **envp)
{
	char	*cmd_path;

	cmd_path = ft_get_command_path(envp, command);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(errno);
	}
	if (mode)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	child_process(pipefd, cmd_path, mode, envp);
	free(cmd_path);
}

void	handle_pipe(char **argv, char **envp)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		fd1;
	int		fd2;

	init_fds(argv[1], argv[4], &fd1, &fd2);
	init_pipe(pipefd);
	pid1 = process_fork();
	if (pid1 == 0)
		execute_child_process(fd1, pipefd, argv[2], 0, envp);
	pid2 = process_fork();
	if (pid2 == 0)
		execute_child_process(fd2, pipefd, argv[3], 1, envp);
	handle_parent_process(pipefd, fd1, fd2, pid1, pid2);
}

int	main(int argc, char **argv, char **envp)
{
	char	*error;

	error = "Uso: ./pipex archivo1 comando1 comando2 archivo2";
	if (argc != 5)
	{
		ft_printf("%s\n", error);
		return (1);
	}
	handle_pipe(argv, envp);
	// system("leaks pipex");
	return (0);
}
