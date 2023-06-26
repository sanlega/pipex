/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:54:17 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/26 21:39:57 by slegaris         ###   ########.fr       */
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
//
// char	*ft_get_command_path(char **envp, char *cmd)
// {
// 	char	*path_var;
// 	char	*result;
// 	char	**cmd_parts;
//
// 	cmd_parts = ft_split(cmd, ' ');
//
// 	path_var = NULL;
// 	while (*envp)
// 	{
// 		if (ft_strncmp(*envp, "PATH=", 5) == 0)
// 		{
// 			path_var = *envp + 5;
// 			break;
// 		}
// 		envp++;
// 	}
// 	result = ft_check_path(path_var, cmd_parts[0]);
// 	if (result)
// 	{
// 		free(cmd_parts[0]);
// 		cmd_parts[0] = result;
// 		return (ft_strjoin(cmd_parts[0], " "));
// 	}
// 	if (access(cmd_parts[0], X_OK) == 0)
// 		return (cmd);
// 	return (free(cmd_parts), NULL);
// }
char *ft_get_path_var(char **envp)
{
    while (*envp)
    {
        if (ft_strncmp(*envp, "PATH=", 5) == 0)
            return (*envp + 5);
        envp++;
    }
    return (NULL);
}

char *ft_check_command_path(char *cmd, char **cmd_parts, char **envp)
{
    char    *result;

    result = ft_check_path(ft_get_path_var(envp), cmd_parts[0]);
    if (result)
    {
        free(cmd_parts[0]);
        cmd_parts[0] = result;
    }
    else if (access(cmd_parts[0], X_OK) == 0)
        result = cmd;
    else
        result = NULL;
    return (result);
}

char *ft_join_cmd_and_args(char **cmd_parts)
{
    int     i;
    char    *command_with_args;
    char    *tmp;

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

char *ft_get_command_path(char **envp, char *cmd)
{
    char    *result;
    char    **cmd_parts;

    cmd_parts = ft_split(cmd, ' ');

    result = ft_check_command_path(cmd, cmd_parts, envp);
    if (result)
        result = ft_join_cmd_and_args(cmd_parts);
    free(cmd_parts);
    return (result);
}
