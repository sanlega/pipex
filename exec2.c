/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegaris <slegaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:48:42 by slegaris          #+#    #+#             */
/*   Updated: 2023/06/22 21:54:43 by slegaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>

#define MAX_ARGS 64

// Prototipo de tu función ft_split
char **ft_split(char *str, char delim);

char excmd(char *command)
{
    char **args = ft_split(command, ' ');

    if (args[0] == NULL)
    {
        printf("Command not specified.\n");
        return 1;
    }

    execve(args[0], args, NULL);

    // Si execve retorna, significa que ha habido un error
    perror("execve");
    return 1;
}

int main(int argc, char **argv)
{
    char *command = argv[1];
    excmd(command);
    return 0;
}
