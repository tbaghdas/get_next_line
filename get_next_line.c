/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btigran <btigran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/04/01 14:50:12 by btigran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_line_cpy(char *old, char *line, int i, int fd)
{
	int	j;
	
	j = 0 + fd * BUFFER_SIZE;
	while (old[i] != '\0')
	{
		line[j++] = old[i++];
	}
}

void	ft_mem_shift(char *old, int start, int limit, int i)
{
	int	idx_shift;
	idx_shift = 0;
	while (i + idx_shift < limit)
	{
		old[start + idx_shift] = old[i + idx_shift];
		idx_shift++;
	}
	while (start + idx_shift < limit)
		old[start + idx_shift++] = '\0';
}

int	ft_avail_line(char *line, char *old, int fd)
{
	int	i;
	int j;
	int	limit;
	int	return_value;

	j = 0;
	i = fd * BUFFER_SIZE;
	limit = i + BUFFER_SIZE;
	while (old[i] != '\n' && i < limit && old[i] != '\0')
		line[j++] = old[i++];
	if (old[i] == '\n')
	{
		line[j] = '\0';
		return_value = -1;
		i++;
	}
	else
		return_value = i - fd * BUFFER_SIZE;
	ft_mem_shift(old, fd * BUFFER_SIZE, limit, i);
	return (return_value);
}


char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	old[RLIMIT_NOFILE * BUFFER_SIZE];
	//static char	*old[5000];
	int			i;
	int			shift;
	int			count;

	int g;

	// if (old[fd] == NULL)
	// 	old[fd] = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0)
		return (NULL);
	count = BUFFER_SIZE;
	i = 0;
	line = (char *)malloc((count + 1) * sizeof(char));
	if (line == NULL)// || old[fd] == NULL)
		return (NULL);
	if (read(fd, line, 0) == -1)
		return (NULL);
	//printf("%s\nkkk\n%s\nggggg\n", line, &old[fd*BUFFER_SIZE]);
	shift = ft_avail_line(line, old, fd);
	if (shift == -1)
		return (line);
	g = read(fd, line + count - BUFFER_SIZE + shift, BUFFER_SIZE - shift);
	line[count - BUFFER_SIZE + shift + g] = '\0';
	if (g == 0)
		i = shift;
	//printf("line: %s\nold: %s\ng: %d\n", line, &old[fd*BUFFER_SIZE], g);
	if (g == -1 || (g == 0 && shift == 0))//############ 0000000000000000000000000000
		return (free(line),NULL);
	while (g > 0)
	{
		//printf("KLKOPO\n");
		i = count - BUFFER_SIZE + shift;
		while (i < count-1 && line[i] != '\n')// && i < count - BUFFER_SIZE + shift + g)
			i++;
		if (line[i] == '\n')// || i == count - BUFFER_SIZE + shift + g)
			break ;
		count += BUFFER_SIZE;
		tmp = (char *)malloc((count + 1) * sizeof(char));
		if (tmp == NULL)
		{
			free(line);
			return (NULL);
		}
		line[i+1] = '\0';
		ft_line_cpy(line, tmp, 0, 0);
		free(line);
		
		line = tmp;
		shift = 0;
		g = read(fd, line + count - BUFFER_SIZE + shift, BUFFER_SIZE - shift);
		line[count - BUFFER_SIZE + shift + g] = '\0';
	}
	if (line[i] == '\n' && g != 1)
		ft_line_cpy(line, old, i + 1, fd);
	line[i] = '\0';
	return (line);
}


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
}

