/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:45:56 by slegaris          #+#    #+#             */
/*   Updated: 2024/06/24 11:00:48 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include <errno.h>

# ifndef BONUS
#  define BONUS 0
# endif

void	child_process(int pipefd[2], char *command, int mode, char **env);
void	handle_pipe(char **argv, char **envp);
char	**ft_split(char const *s, char c);
char	*ft_check_path(char *path_var, char *cmd, char *command);
char	*ft_get_command_path(char **envp, char *cmd);
void	init_fds(char *file1, char *file2, int *fds, char **av);
void	init_pipe(int *pipefd);
int		process_fork(void);
void	dotcomma_error(char *cmd);
void	handle_parent_process(int *pipefd, int *fds, int pid1, int pid2);
char	*dot_slash_check(char *path, char *cmd, char *command);
int		check_enviorement(char **envp);
int		is_absolute(char *path);
int		no_access(char *cmd);
char	*parse_path(char *path_var, char *cmd, char *path_end);
char	*esejoint(char *str1, char *str2);
char	**esesplit(char *str, char c);
char	*esesubstr(char *s, int start, size_t len);
void	ft_error(char *str);
void	normal_open_fds(int *fds, char *file1, char *file2);

#endif
