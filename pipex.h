/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:45:56 by slegaris          #+#    #+#             */
/*   Updated: 2023/08/15 15:36:06 by slegaris         ###   ########.fr       */
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


void	child_process(int pipefd[2], char *command, int mode);
void	handle_pipe(char **argv, char **envp);
char	**ft_split(char const *s, char c);
char	*ft_check_path(char *path_var, char *cmd);
char	*ft_get_command_path(char **envp, char *cmd);
void	child_process(int pipefd[2], char *command, int mode);
void	init_fds(char *file1, char *file2, int *fd1, int *fd2);
void	init_pipe(int *pipefd);
int	process_fork(void);

#endif
