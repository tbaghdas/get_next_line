/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btigran <btigran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/04/02 20:27:16 by btigran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//header y 

#include "get_next_line.h"

void	ft_line_cpy(char *old, char *line, int i)
{
	int	j;

	j = 0;
	while (old[i] != '\0')
	{
		line[j++] = old[i++];
	}
}

int	ft_avail_line(char *line, char *old, int i, int j)
{
	int	limit;
	int	return_value;
	int	idx_shift;

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
		return_value = i;
	idx_shift = 0;
	while (i + idx_shift < limit)
	{
		old[idx_shift] = old[i + idx_shift];
		idx_shift++;
	}
	while (idx_shift < limit)
		old[idx_shift++] = '\0';
	return (return_value);
}

char	*ft_check_and_init(int *count, char **old, int fd)
{
	char	*line;
	int		i;

	if (fd < 0 || fd > 5000)
		return (NULL);
	*count = BUFFER_SIZE;
	if (*old == NULL)
	{
		*old = (char *)malloc((*count + 1) * sizeof(char));
		if (old == NULL)
			return (NULL);
		i = 0;
		while (i < *count + 1)
			(*old)[i++] = '\0';
	}
	line = (char *)malloc((*count + 2) * sizeof(char));
	if (line == NULL)
		return (NULL);
	if (read(fd, line, 0) == -1)
		return (free(line), NULL);
	return (line);
}

int	ft_while_body(int *arr, char **line, int *count, int fd)
{
	char	*tmp;
	int		*i;
	int		*shift;
	char	*ln;

	ln = *line;
	shift = &arr[1];
	i = &arr[2];
	*i = *count - BUFFER_SIZE + *shift;
	while (*i < *count - 1 && ln[*i] != '\n')
		(*i)++;
	if (ln[*i] == '\n')
		return (-2);
	*count += BUFFER_SIZE;
	tmp = (char *)malloc((*count + 2) * sizeof(char));
	if (tmp == NULL)
		return (free(*line), -1);
	ln[*i + 1] = '\0';
	ft_line_cpy(*line, tmp, 0);
	free(*line);
	*line = tmp;
	*shift = 0;
	arr[0] = read(fd, *line + *count - BUFFER_SIZE, BUFFER_SIZE);
	ln[*count - BUFFER_SIZE + arr[0]] = '\0';
	return (1);
}

int	ft_reading_file(char **ln, char *old, int *count, int fd)
{
	int		ar[4];
	char	*line;

	line = *ln;
	ar[1] = ft_avail_line(*ln, old, 0, 0);
	if (ar[1] == -1)
		return (-2);
	ar[2] = 0;
	ar[0] = read(fd, *ln + *count - BUFFER_SIZE + ar[1], BUFFER_SIZE - ar[1]);
	line[*count - BUFFER_SIZE + ar[1] + ar[0]] = '\0';
	if (ar[0] == 0)
		ar[2] = ar[1];
	if (ar[0] == -1 || (ar[0] == 0 && ar[1] == 0))
		return (free(*ln), -1);
	while (ar[0] > 0)
	{
		arr[3] = ft_while_body(ar, ln, count, fd);
		if (arr[3] == -1)
			return (arr[3]);
		if (arr[3] == -2)
			break ;
	}
	if (line[ar[2]] == '\n' && ar[0] != 1)
		ft_line_cpy(*ln, old, ar[2] + 1);
	return (ar[2]);
}
