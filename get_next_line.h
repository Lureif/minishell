/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <brjorgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 00:02:25 by brjorgen          #+#    #+#             */
/*   Updated: 2019/04/24 17:52:01 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# define BUFF_SIZE 4096

int					get_next_line(const int fd, char **line);
typedef struct		s_vars
{
	size_t			buf;
	size_t			len;
	char			c;
	int				ret;
}					t_vars;
typedef struct		s_getc_vars
{
	char			tmp[BUFF_SIZE];
	int				i;
	int				len;
}					t_getc_vars;

#endif
