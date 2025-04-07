/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/04/07 22:24:06 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*old;
	int			count;
	int			i;
	int			arr[5];

	arr[4] = fd;
	line = ft_check_and_init(&count, &old, fd);
	if (line == NULL)
		return (NULL);
	i = ft_reading_file(&line, old, &count, arr);
	if (i == -1)
		return (NULL);
	if (i == -2)
		return (line);
	line[++i] = '\0';
	return (line);
}
/*

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//#define BUFFER_SIZE 32

// Prototype for your get_next_line function 
//(adjust this according to your project)
char *get_next_line(int fd);

int main(int argc, char **argv)
{
    int fd;
    char *line;
	int len = 0;
int b = 0;
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
    while ((line = get_next_line(fd)) != NULL && b++ < 19)
    {
        //printf("line: %s", line);
		printf("%d: %s", b, line);
		//write(1, line, strlen(line));
        if (line)
			free(line);  // Free the memory allocated by get_next_line
		//write(1, "\n", 1);
    }

    close(fd);
    return (0);
}
*/