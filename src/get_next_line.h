/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:28:01 by paranha           #+#    #+#             */
/*   Updated: 2023/12/07 17:11:29 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_listt
{
	char			*content;
	size_t			length;
	struct s_listt	*next;
}					t_listt;

void				enqueue(t_listt **lst, t_listt *new);
t_listt				*get_tail(t_listt *lst);
t_listt				*create_node(char *content);
void				*ft_memcpy(void *dest, const void *src, size_t n);
t_listt				*cleanup_on_error(t_listt **stash, t_listt *new,
						int bytes_read);
char				*get_next_line(int fd);

#endif
