/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btigran <btigran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/04/09 16:53:21 by btigran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		line[j] = '\n';
		line[j + 1] = '\0';
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

	if (fd < 0 || fd > FOPEN_MAX)
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
	line = (char *)malloc((*count * 2 + 2) * sizeof(char));
	if (line == NULL)
		return (free(*old), *old = NULL, NULL);
	return (line);
}

int	ft_while_body(int *arr, char **line, int *count, int fd)
{
	char	*tmp;
	int		*shift;
	char	*ln;

	ln = *line;
	shift = &arr[1];
	arr[2] = *count - BUFFER_SIZE;
	while (arr[2] < *count - 1 && ln[arr[2]] != '\n' && ln[arr[2]] != '\0')
		(arr[2])++;
	if (ln[arr[2]] == '\n' || arr[0] < BUFFER_SIZE)
		return (-2);
	*count += BUFFER_SIZE;
	tmp = (char *)malloc((*count + 2) * sizeof(char));
	if (tmp == NULL)
		return (free(*line), *line = NULL, -1);
	ln[arr[2] + 1] = '\0';
	ft_line_cpy(*line, tmp, 0);
	free(*line);
	*line = tmp;
	ln = *line;
	*shift = 0;
	arr[0] = read(fd, *line + *count - BUFFER_SIZE, BUFFER_SIZE);
	ln[*count - BUFFER_SIZE + arr[0]] = '\0';
	return (1);
}

int	ft_reading_file(char **ln, char **old, int *count, int *ar)
{
	char	*line;

	line = *ln;
	ar[1] = ft_avail_line(*ln, *old, 0, 0);
	if (ar[1] == -1)
		return (-2);
	*count += ar[1];
	ar[0] = read(ar[4], *ln + *count - BUFFER_SIZE, BUFFER_SIZE);
	line[*count - BUFFER_SIZE + ar[0]] = '\0';
	ar[2] = ar[0];
	if (ar[0] == 0)
		ar[2] = ar[1];
	if (ar[0] == -1 || (ar[0] == 0 && ar[1] == 0))
		return (free(*ln), *ln = NULL, free(*old), *old = NULL, -1);
	while (ar[0] > 0)
	{
		ar[3] = ft_while_body(ar, ln, count, ar[4]);
		if (ar[3] == -1)
			return (free(*old), *old = NULL, ar[3]);
		if (ar[3] == -2)
			break ;
	}
	if (*(*ln + ar[2]) == '\n' && ar[0] != 1)
		ft_line_cpy(*ln, *old, ar[2] + 1);
	return (ar[2]);
}
