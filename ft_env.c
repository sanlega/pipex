/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:54:17 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/26 20:16:59 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_check_path(char *path_var, char *cmd)
{
	char	*path;
	char	*path_end;
	char	*abs_path;
	char	*path_with_slash;

	while ((path_end = ft_strchr(path_var, ':')))
	{
		path = ft_substr(path_var, 0, path_end - path_var);
		path_with_slash = ft_strjoin(path, "/");
		abs_path = ft_strjoin(path_with_slash, cmd);
		free(path);
		free(path_with_slash);
		if (access(abs_path, X_OK) == 0)
			return (abs_path);
		free(abs_path);
		path_var = path_end + 1;
	}
	return (NULL);
}

char	*ft_get_command_path(char **envp, char *cmd)
{
	char	*path_var;
	char	*result;
	char	**cmd_parts;

	cmd_parts = ft_split(cmd, ' ');

	path_var = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path_var = *envp + 5;
			break;
		}
		envp++;
	}
	result = ft_check_path(path_var, cmd_parts[0]);
	if (result)
	{
		free(cmd_parts[0]);
		cmd_parts[0] = result;
		return (ft_strjoin(cmd_parts[0], " "));
	}
	if (access(cmd_parts[0], X_OK) == 0)
		return (cmd);
	return (free(cmd_parts), NULL);
}
