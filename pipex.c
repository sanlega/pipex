/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanlega <sanlega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:44:49 by slegaris          #+#    #+#             */
/*   Updated: 2024/06/24 21:26:47 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	execute_child_mode0(int fd, int *pipefd, char *command, char **envp)
{
	int		mode;
	char	*cmd_path;

	mode = 0;
	cmd_path = ft_get_command_path(envp, command);
	if (!cmd_path)
	{
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putendl_fd(command, 2);
		exit(errno);
	}
	if (fd < 0)
		ft_error("open");
	dup2(fd, STDIN_FILENO);
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
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putendl_fd(command, 2);
		exit(errno);
	}
	if (fd < 0)
		ft_error("open");
	dup2(fd, STDOUT_FILENO);
	child_process(pipefd, cmd_path, mode, envp);
	free(cmd_path);
}

void	handle_pipe(char **argv, char **envp)
{
	int		pipefd[2];
	int		pids[2];
	int		fds[2];

	init_fds(argv[1], argv[4], fds, argv);
	init_pipe(pipefd);
	pids[0] = process_fork();
	if (pids[0] == 0)
	{
		if (BONUS == 1)
			execute_child_mode0(fds[0], pipefd, argv[3], envp);
		else
			execute_child_mode0(fds[0], pipefd, argv[2], envp);
	}
	pids[1] = process_fork();
	if (pids[1] == 0)
	{
		if (BONUS == 1)
			execute_child_mode1(fds[1], pipefd, argv[4], envp);
		else
			execute_child_mode1(fds[1], pipefd, argv[3], envp);
	}
	handle_parent_process(pipefd, fds, pids[0], pids[1]);
}

int	main(int argc, char **argv, char **envp)
{
	char	*error;

	error = "Usage: ./pipex file1 command1 command2 file2";
	if ((BONUS == 1 && (argc != 6 || ft_strncmp(argv[1], "heredoc", 7) != 0))
		|| (BONUS != 1 && argc != 5))
	{
		ft_printf("%s\n", error);
		return (1);
	}
	handle_pipe(argv, envp);
	if (BONUS == 1 && argc == 6 && ft_strncmp(argv[1], "heredoc", 7) == 0)
		unlink(".heredoc");
	return (0);
}
