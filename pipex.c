/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:44:49 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/10 19:39:44 by slegaris         ###   ########.fr       */
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

void	handle_parent_process(int *pipefd, int *fds, int pid1, int pid2)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	execute_child_process(int fd, int *pipefd, char *command, int mode, char **envp)
{
	char	*cmd_path;
	int	mode;

	mode = 1;
	cmd_path = ft_get_command_path(envp, command);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(errno);
	}
	if (mode)
	{
		dup2(fd, STDOUT_FILENO);
		mode = 0;
	}
	else
		dup2(fd, STDIN_FILENO);
	child_process(pipefd, cmd_path, mode, envp);
	free(cmd_path);
}

void	handle_pipe(char **argv, char **envp)
{
	int		pipefd[2];
	int		pids[2];
	int		fds[2];

	init_fds(argv[1], argv[4], fds);
	init_pipe(pipefd);
	pids[0] = process_fork();
	if (pids[0] == 0)
		execute_child_process(fds[0], pipefd, argv[2], 0, envp);
	pids[1] = process_fork();
	if (pids[1] == 0)
		execute_child_process(fds[1], pipefd, argv[3], 1, envp);
	handle_parent_process(pipefd, fds, pids[0], pids[1]);
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
	return (0);
}
