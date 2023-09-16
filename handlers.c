/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:53:40 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/16 15:52:27 by slegaris         ###   ########.fr       */
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

char	*dot_slash_check(char *path, char *cmd, char *command)
{
	path = ft_substr(cmd, 2, ft_strlen(cmd));
	if (access(command, F_OK) == -1)
		dotcomma_error(path);
	return (cmd);
}

int	check_access(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (0);
	else
		return (1);
}

int	is_absolute(char *path)
{
	if (ft_strncmp("/", path, 1) == 0)
		return (1);
	if (ft_strncmp("./", path, 2) == 0)
		return (1);
	if (ft_strncmp("../", path, 3) == 0)
		return (1);
	return (0);
}

char	*parse_path(char *path_var, char *cmd, char *path_end)
{
	char	*path;
	char	*abs_path;
	char	*path_with_slash;

	path = ft_substr(path_var, 0, path_end - path_var);
	path_with_slash = ft_strjoin(path, "/");
	abs_path = ft_strjoin(path_with_slash, cmd);
	free(path);
	free(path_with_slash);
	return (abs_path);
}
