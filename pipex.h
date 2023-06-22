/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:45:56 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/22 04:55:56 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"

void	child_process(int pipefd[2], char *command, int mode);
void	handle_pipe(char *command1, char *command2);
char	**ft_split(char const *s, char c);

#endif
