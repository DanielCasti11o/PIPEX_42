/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repaso.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:10:22 by dacastil          #+#    #+#             */
/*   Updated: 2025/03/15 18:11:17 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h> 

int	main()
{
int	pipefd[2]; // creamos un pipe con dos extremos
pid_t pid1, pid2   // extremos del pipe que contendran la lectura y escritura
// pid 1 lectura ----> pid 2 escritura

pip1 = fork();
if (pid1 < 0) // si es menor que 0 ha habido error
{
	perror("pip1 error"); // Muestra un mensaje de error
	exit (1);
}
if (pid1 == 0)
{
	close(pid1); // cerramos el fd que no necesitamos en este proceso hijo en concreto
	dup2(pid2, STDOUT_FILENO); // redirige la salida del fd2 al fd1 
	// exec command
	close(pid2) // command
}
pip2 = fork()
if(pid2 < 0)
{
	perror("pid2 error");
	exit(1);
}
if (pid2 == 0)
{
 	close(pid2);
	dup2(pid1, STDIN_FILENO);
	//exec command
	close (pid1) // command
}

waitpid(pid2);
waitpid(pid1);
close(pid1);
close(pid2);

}
