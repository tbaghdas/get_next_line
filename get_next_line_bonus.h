/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btigran <btigran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:38 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/04/08 19:50:41 by btigran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
void	ft_line_cpy(char *old, char *line, int i);
int		ft_avail_line(char *line, char *old, int i, int j);
char	*ft_check_and_init(int *count, char **old, int fd);
int		ft_while_body(int *arr, char **line, int *count, int fd);
int		ft_reading_file(char **ln, char **old, int *count, int *ar);

#endif