/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanlega <sanlega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:44:49 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/11 14:41:17 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child_mode0(int fd, int *pipefd, char *command, char **envp)
{
	int		mode;
	char	*cmd_path;
	// char	**enviorement;

	mode = 0;
	cmd_path = ft_get_command_path(envp, command);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(errno);
	}
	dup2(fd, STDIN_FILENO);
	// if (check_enviorement(envp) == 0)
	// 	enviorement = NULL;
	// else
	// 	enviorement = envp;
	child_process(pipefd, cmd_path, mode, envp);
	free(cmd_path);
}

void	execute_child_mode1(int fd, int *pipefd, char *command, char **envp)
{
	char	*cmd_path;
	int		mode;

	mode = 1;
	cmd_path = ft_get_command_path(envp, command);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(errno);
	}
	dup2(fd, STDOUT_FILENO);
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
		execute_child_mode0(fds[0], pipefd, argv[2], envp);
	pids[1] = process_fork();
	if (pids[1] == 0)
		execute_child_mode1(fds[1], pipefd, argv[3], envp);
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
