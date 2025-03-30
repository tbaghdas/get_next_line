/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/03/30 16:15:06 by tbaghdas         ###   ########.fr       */
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
	//printf("OOOOOOOO gg OOOOOO %d %d\n", start, limit);
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
	//printf("VVVVVV %d %c\n", old[i], old[i]);
	while (old[i] != '\n' && i < limit && old[i] != '\0')
		line[j++] = old[i++];
	if (old[i] == '\n')
	{
		//line[j++] = '\n';
		line[j] = '\0';
		return_value = -1;
		i++;
	}
	else
		return_value = i - fd * BUFFER_SIZE;
	ft_mem_shift(old, fd * BUFFER_SIZE, limit, i);
	return (return_value);
}

// void	set_zero(char *arr, int size)
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < size)
// 		arr[i++] = '\0';
// }

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	old[1000 * BUFFER_SIZE];
	int			i;
	int			shift;
	int			count;

	int g;

	if (fd < 0)
		return (NULL);
	count = BUFFER_SIZE;
	i = 0;
	line = (char *)malloc(count * sizeof(char));
	if (line == NULL)
		return (NULL);
	if (read(fd, line, 0) == -1)
		return (NULL);
	shift = ft_avail_line(line, old, fd);
	if (shift == -1)
		return (line);
	g = read(fd, line + count - BUFFER_SIZE + shift, BUFFER_SIZE - shift);
	if (g == -1 || g == 0)// || g < BUFFER_SIZE)
		return (free(line), NULL);
	while (g != -1)//  && g >= BUFFER_SIZE)
	{
		i = count - BUFFER_SIZE + shift;
		while (line[i] != '\n' && i < count)// -g)//&& i < g)
			i++;
		if (i != count || (g == 1 && line[i] == '\n'))
			break ;
		count += BUFFER_SIZE;
		//printf("%d\n", count);
		tmp = (char *)malloc(count * sizeof(char));
		if (tmp == NULL)
		{
			free(line);
			return (NULL);
		}
		ft_line_cpy(line, tmp, 0, 0);
		free(line);
		
		line = tmp;
		shift = 0;
		//printf("%d %d %d %d kkk\n", count - BUFFER_SIZE + shift, BUFFER_SIZE - shift, shift, count);
		g = read(fd, line + count - BUFFER_SIZE + shift, BUFFER_SIZE - shift);
		//printf("g: %d \n", g);
	}
	if (line[i] == '\n' && g != 1)
		ft_line_cpy(line, old, i + 1, fd);
	//line[i++] = '\n';
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
        free(line);  // Free the memory allocated by get_next_line
		write(1, "\n", 1);
    }

    close(fd);
    return (0);
}

