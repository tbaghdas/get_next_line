/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btigran <btigran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/04/01 23:44:36 by btigran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	//static char	old[RLIMIT_NOFILE * BUFFER_SIZE];
	static char	*old[5000];
	int			count;
	int			i;

	line = ft_check_and_init(&count, &old[fd], fd);
	if (line == NULL)
		return (NULL);
	i = ft_reading_file(&line, old[fd], &count, fd);
	if (i == -1)
		return (NULL);
	if (i == -2)
		return (line);
	line[i] = '\0';
	return (line);
}
/*

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//#define BUFFER_SIZE 32

// Prototype for your get_next_line function (adjust this according to your project)
char *get_next_line(int fd);

int main(int argc, char **argv)
{
    int fd;
    char *line;
	int len = 0;

    if (argc != 2)
    {
        write(1, "Usage: ./a.out <filename>\n", 25);
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Read and print lines until EOF
    while ((line = get_next_line(fd)) != NULL)
    {
        //printf("line: %s", line);
		
		write(1, line, strlen(line));
        if (line)
			free(line);  // Free the memory allocated by get_next_line
		write(1, "\n", 1);
    }

    close(fd);
    return (0);
}*/
