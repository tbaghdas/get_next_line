/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btigran <btigran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/03/07 18:19:40 by btigran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	ft_line_cpy(char *old, char *line, int i, int fd)
{
	int	j;
	
	j = 0;
	while (old[i])
	{
		line[j + fd] = old[i++];
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
		old[start + idx_shift++] = 0;
}

int	ft_avail_line(char *line, char *old, int fd)
{
	int	i;
	int j;
	int	limit;
	int	return_value;

	j = 0;
	i = fd * 10;
	limit = (fd + 1) * 10;
	while (old[i] != '\n' && i < limit)
		line[j++] = old[i++];
	if (i < limit)
	{
		line[j] = '\n';
		return_value = -1;
	}
	else if (old[i - 1] == '\n')
		return_value = -1;
	else
		return_value = i - fd * 10;
	ft_mem_shift(old, fd * 10, limit, i);
	return (return_value);
}

char	*get_next_line(int fd)
{
	//char		buf[10];
	char		*line;
	char		*tmp;
	static char	old[10000];
	int			i;
	int			shift;

	count = 10;
	i = 0;
	line = (char *)malloc(count * sizeof(char));
	if (line == NULL)
		return (NULL);
	shift = ft_avail_line(line, old, fd);
	if (shift == -1)
		return (line);
	while (read(fd, line + count - 10 + shift, 10 - shift))
	{
		i = count - 10 + shift;
		while (line[i] != '\0')
			i++;
		if (i != count)
			break ;
		count *= 10;
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
	}
	ft_line_cpy(line, old, i, fd);
	return (line);
}
