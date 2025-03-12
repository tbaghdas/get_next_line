/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/03/12 21:55:29 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_line_cpy(char *old, char *line, int i, int fd)
{
	int	j;
	
	j = 0 + fd * BUFFER_SIZE;
	while (old[i] != '\0')
	{
		// printf("TPMA %d\n", old[i]);
		line[j++] = old[i++];
	}
	// printf("KLKLKLLKKKK %s plt\n", &line[fd*BUFFER_SIZE]);
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
	int t = 0;
	// while (t < 33)
	// 	printf("FFFF: %c %d\n", old[i + t], t++);
	while (old[i] != '\n' && i < limit && old[i] != '\0')
		line[j++] = old[i++];
	// printf("nnnnnn %d\n", i);
	//if ((old[i] == '\n' && i == limit) || old[i - 1] == '\n')
	if (old[i - 1] == '\n')
	{
		line[j++] = '\n';
		line[j] = '\0';
		return_value = -1;
	}
	// else if (old[i - 1] == '\n')
	// 	return_value = -1;
	else
		return_value = i - fd * BUFFER_SIZE;
	// printf("QQQ %d %d \n", i, fd);
	ft_mem_shift(old, fd * BUFFER_SIZE, limit, i);
	return (return_value);
}

void	set_zero(char *arr, int size)
{
	int	i;
	
	i = 0;
	while (i < size)
		arr[i++] = '\0';
}

char	*get_next_line(int fd)
{
	//char		buf[10];
	char		*line;
	char		*tmp;
	static char	old[1000 * BUFFER_SIZE];
	int			i;
	int			shift;
	int			count;

int g;

	// printf("TEBAOLDYDEMI: %s popon\n", &old[fd*BUFFER_SIZE]);
	count = BUFFER_SIZE;
	i = 0;
	if (read(fd, line, 0) == -1)
		return (NULL);
	line = (char *)malloc(count * sizeof(char));
	if (line == NULL)
		return (NULL);
	// set_zero(old, 1000 * BUFFER_SIZE);
	shift = ft_avail_line(line, old, fd);
	//printf("\n shift %d\n", shift);
	if (shift == -1)
		return (line);
	g = read(fd, line + count - BUFFER_SIZE + shift, BUFFER_SIZE - shift);
	// printf("xcho %d %d %d\n", g, count, shift);
	if (g == -1 || g < BUFFER_SIZE)
		return (NULL);
	while (g != -1  && g >= BUFFER_SIZE)
	{
		//printf("UUUUUU  %d  \n", g);
		//printf("testing : %s ##\n %d %d %d \n", line, count, shift, g);
		i = count - BUFFER_SIZE + shift;
		while (line[i] != '\n' && i < count)
			i++;
		if (i != count)
			break ;
		count += BUFFER_SIZE;
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
		g = read(fd, line + count - BUFFER_SIZE + shift, BUFFER_SIZE - shift);
	}
	// printf("VVVVVVV %d  %s\n", i, &line[i]);
	ft_line_cpy(line, old, ++i, fd);
	// printf("TEBAOLDY: %s popo\n", &old[fd*BUFFER_SIZE]);
	line[i++] = '\n';
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
        printf("%s", line);
        free(line);  // Free the memory allocated by get_next_line
    }

    close(fd);
    return (0);
}

