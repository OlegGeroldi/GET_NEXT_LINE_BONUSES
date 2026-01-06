/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olunichk <olunichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:10:13 by olunichk          #+#    #+#             */
/*   Updated: 2026/01/06 15:59:26 by olunichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
//char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, char c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif