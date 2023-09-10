/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:45:56 by slegaris          #+#    #+#             */
/*   Updated: 2023/09/10 20:06:46 by slegaris         ###   ########.fr       */
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

void	child_process(int pipefd[2], char *command, int mode, char **env);
void	handle_pipe(char **argv, char **envp);
char	**ft_split(char const *s, char c);
char	*ft_check_path(char *path_var, char *cmd, char *command);
char	*ft_get_command_path(char **envp, char *cmd);
void	init_fds(char *file1, char *file2, int *fds);
void	init_pipe(int *pipefd);
int		process_fork(void);
void	dotcomma_error(char *cmd);
void	handle_parent_process(int *pipefd, int *fds, int pid1, int pid2);

#endif
