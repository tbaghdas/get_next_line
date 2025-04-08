/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btigran <btigran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/04/08 23:34:30 by btigran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*old[FOPEN_MAX];
	int			count;
	int			i;
	int			arr[5];

	arr[4] = fd;
	line = ft_check_and_init(&count, &old[fd], fd);
	if (line == NULL)
		return (NULL);
	i = ft_reading_file(&line, &old[fd], &count, arr);
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
}
*/
/*
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd1;
    int fd2;
    char *line = NULL;
    char *line2 = NULL;
    int fd3;
    int fd4;
    char *line3 = NULL;
    char *line4 = NULL;
	int len = 0;
int b = 0;
    if (argc < 2)
    {
        write(1, "Usage: ./a.out <filename>\n", 25);
        return (1);
    }

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[1], O_RDONLY);
    fd3 = open(argv[1], O_RDONLY);


    
    line2 = get_next_line(fd1);		
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
			free(line2);
		}
    line2 = get_next_line(fd2);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
			free(line2);
		}
    line2 = get_next_line(fd3);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
			free(line2);
		}
    line2 = get_next_line(fd1);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
			free(line2);
		}
    line2 = get_next_line(fd2);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
			free(line2);
		}
    line2 = get_next_line(fd2);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
			free(line2);
		}
    fd4 = open(argv[2], O_RDONLY);



    line2 = get_next_line(fd2);		
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
			free(line2);
		}
    line2 = get_next_line(fd3);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
			free(line2);
		}
    line2 = get_next_line(fd4);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
            write(1, "\nGGGG\n", 6);
			free(line2);
		}
    line2 = get_next_line(fd2);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
            write(1, "\nGFFG\n", 6);
			free(line2);
		}
    line2 = get_next_line(fd2);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
            write(1, "\nGDDG\n", 6);
			free(line2);
		}
    line2 = get_next_line(fd1);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
            write(1, "\nGKKG\n", 6);
			free(line2);
		}
    line2 = get_next_line(fd4);	
    if (line2 != NULL)
		{
			write(1, line2, strlen(line2));
            write(1, "\nGLLG\n", 6);
			free(line2);
		}
    
    // if (fd == -1)
    // {
    //     perror("Error opening file");
    //     return (1);
    // }

    // Read and print lines until EOF
    // while (line != NULL || line2 != NULL || b < 19)
    // {
    //     //printf("line: %s", line);
	// 	//printf("%d: %s\n", b, line);
	// 	//printf("%d: %s\n", b, line2);
    //     if (line)
	// 	{
	// 		write(1, line, strlen(line));
	// 		free(line);  // Free the memory allocated by get_next_line
	// 	}
	// 	if (line2 != NULL)
	// 	{
	// 		write(1, line2, strlen(line2));
	// 		free(line2);
	// 	}
	// 	if (b == 2)
	// 	{
	// 		close(fd);
	// 		fd = open(argv[1], O_RDONLY);
	// 	}
	// 	//write(1, "\n", 1);
	// 	line = get_next_line(fd);
	// 	line2 = get_next_line(fd2);
	// 	++b;
    // }

   // close(fd);
    return (0);
}
*/