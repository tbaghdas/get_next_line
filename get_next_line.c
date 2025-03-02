/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:33 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/03/02 18:25:35 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	ft_line_cpy(old, line, i, fd)
{
	int	j;
	
	j = 0;
	while (old[i])
	{
		line[j + fd] = old[i++];
	}
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
	ft_avail_line();
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
		ft_line_cpy(line, tmp, 0, 0);
		free(line);
		line = tmp;
	}
	ft_line_cpy(line, old, i, fd);
	return (line);
}
