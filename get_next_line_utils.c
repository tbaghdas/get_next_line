header y 
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
	line = (char *)malloc((*count + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	if (read(fd, line, 0) == -1)
		return (free(line), NULL);
	return (line);
}

int	ft_while_body(int *arr, char **line, int *count, int fd)
{
	char	*tmp;
	int		*g;
	int		*i;
	int		*shift;

	g = &arr[0];
	shift = &arr[1];
	i = &arr[2];
	*i = *count - BUFFER_SIZE + *shift;
	while (*i < *count - 1 && (*line)[*i] != '\n')
		(*i)++;
	if ((*line)[*i] == '\n')
		return (-2);
	*count += BUFFER_SIZE;
	tmp = (char *)malloc((*count + 1) * sizeof(char));
	if (tmp == NULL)
		return (free(*line), -1);
	(*line)[*i + 1] = '\0';
	ft_line_cpy(*line, tmp, 0);
	free(*line);
	*line = tmp;
	*shift = 0;
	*g = read(fd, *line + *count - BUFFER_SIZE + *shift, BUFFER_SIZE - *shift);
	(*line)[*count - BUFFER_SIZE + *shift + *g] = '\0';
	return (1);
}

int	ft_reading_file(char **ln, char *old, int *count, int fd)
{
	int		check;
	int		ar[3];

	ar[1] = ft_avail_line(*ln, old, 0, 0);
	if (ar[1] == -1)
		return (-2);
	ar[2] = 0;
	ar[0] = read(fd, *ln + *count - BUFFER_SIZE + ar[1], BUFFER_SIZE - ar[1]);
	(*ln)[*count - BUFFER_SIZE + ar[1] + ar[0]] = '\0';
	if (ar[0] == 0)
		ar[2] = ar[1];
	if (ar[0] == -1 || (ar[0] == 0 && ar[1] == 0))
		return (free(*ln), -1);
	while (ar[0] > 0)
	{
		check = ft_while_body(ar, ln, count, fd);
		if (check == -1)
			return (check);
		if (check == -2)
			break ;
	}
	if ((*ln)[ar[2]] == '\n' && ar[0] != 1)
		ft_line_cpy(*ln, old, ar[2] + 1);
	return (ar[2]);
}
