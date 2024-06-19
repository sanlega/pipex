/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanlega <sanlega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:44:49 by slegaris          #+#    #+#             */
/*   Updated: 2024/06/19 22:28:08 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"


#include <stdio.h>

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

    printf("here: %d", fds[0]);

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

	error = "Uso: ./pipex archivo1 comando1 comando2 archivo2";

	if (BONUS == 1 && (argc != 6 || ft_strncmp(argv[1], "heredoc", 7) != 0))
	{
		printf("BONUS = %d", BONUS);
		ft_printf("AAAAAAAAAAA\n", error);
		return (1);
	}
    else if (argc != 5 && argc != 6)
	{
		printf("BONUS = %d", BONUS);
		ft_printf("%s\n", error);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) != 0) 
		ft_printf("ALOLOLLSLSD\n");

	handle_pipe(argv, envp);
	return (0);
}
