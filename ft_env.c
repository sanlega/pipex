/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:54:17 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/08 05:33:22 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

char	*ft_check_path(char *path_var, char *cmd, char *command)
{
	char	*path;
	char	*path_end;
	char	*abs_path;
	char	*path_with_slash;

	path_end = ft_strchr(path_var, ':');
	if (ft_isalnum(command[0]) > 0)
		while (path_end)
		{
			path = ft_substr(path_var, 0, path_end - path_var);
			path_with_slash = ft_strjoin(path, "/");
			abs_path = ft_strjoin(path_with_slash, cmd);
			free(path);
			free(path_with_slash);
			if (access(abs_path, F_OK) == 0)
				return (abs_path);
			free(abs_path);
			path_var = path_end + 1;
			path_end = ft_strchr(path_var, ':');
		}
	if (command[0] == '.' && command[1] == '/')
	{
		path = ft_substr(cmd, 2, ft_strlen(cmd));
		if (access(command, F_OK) == -1)
			dotcomma_error(path);
		else;
			return (cmd);
	}
	return (NULL);
}

char	*ft_get_path_var(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*ft_check_command_path(char *cmd, char **cmd_parts, char **envp)
{
	char	*result;

	result = ft_check_path(ft_get_path_var(envp), cmd_parts[0], cmd);
	if (cmd[0] == '/')
		result = NULL;
	if (cmd[0] == '.' && cmd[1] == '/')
		result = cmd;
	else
		if (result)
		{
			free(cmd_parts[0]);
			cmd_parts[0] = result;
		}
		if (access(cmd_parts[0], X_OK) == 0)
			result = cmd;
		else
			result = NULL;
	return (result);
}

char	*ft_join_cmd_and_args(char **cmd_parts)
{
	int		i;
	char	*command_with_args;
	char	*tmp;

	i = 0;
	command_with_args = ft_strdup(cmd_parts[i]);
	i++;
	while (cmd_parts[i])
	{
		tmp = ft_strjoin(command_with_args, " ");
		free(command_with_args);
		command_with_args = ft_strjoin(tmp, cmd_parts[i]);
		free(tmp);
		i++;
	}
	return (command_with_args);
}

char	*ft_get_command_path(char **envp, char *cmd)
{
	char	*result;
	char	**cmd_parts;

	cmd_parts = ft_split(cmd, ' ');
	result = ft_check_command_path(cmd, cmd_parts, envp);
	if (result)
		result = ft_join_cmd_and_args(cmd_parts);
	free(cmd_parts);
	return (result);
}
