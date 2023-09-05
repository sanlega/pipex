# Notas

Para ejecutar comandos:

``` C
#include <stdio.h>
#include <unistd.h>

#define MAX_ARGS 64

// Prototipo de tu función ft_split
char **ft_split(char *str, char *delim);

char excmd(char *command)
{
    char **args = ft_split(command, " ");

    if (args[0] == NULL)
    {
        printf("Command not specified.\n");
        return 1;
    }

    execve(args[0], args, NULL);  // asumimos que las variables de entorno existentes están bien

    // Si execve retorna, significa que ha habido un error
    perror("execve");
    return 1;
}

int main()
{
    char command[] = "/bin/ls -l";
    excmd(command);
    return 0;
}
```
se le puede pasar a la funcion un argumento, el path para que ejecute
el comando deseado.

# PATHS:

execve recibe los Path de este manera:

- /bin/ls -la

Para saber donde se encuentran los comandos para probar se puede usar "which <nombre comando>"

ERRORES:
- El programa pilla los comandos con y sin el path absoluto pero no permite añadir el resto del comando al executer.
- Los exitcodes y errores no están del todo bien

Añadir el fd y el pipe como variables en la funciona del fork