

void	ft_line_cpy(old, line, i, fd)
{

}

char	*get_next_line(int fd)
{
	//char		buf[10];
	char		*line;
	char		*tmp;
	static char	old[10000];
	int			i;

	count = 10;
	i = 0;
	line = (char *)malloc(count * sizeof(char));
	if (line == NULL)
		return (NULL);
	while (read(fd, line + count - 10, 10))
	{
		i = count - 10;
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
		ft_line_cpy(line, tmp, 0, fd);
		free(line);
		line = tmp;
	}
	ft_line_cpy(line, old, i, fd);
	return (line);
}
