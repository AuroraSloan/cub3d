/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  get_next_line_utils.c                                :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompso <jthompso@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:43:30 by jthompso          #+#    #+#             */
/*  Updated: 2021/05/14 19:50:01 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	find_char(const char *s, int c)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = 1;
	while (s[i])
	{
		if (s[i++] == (char)c)
			return (ret);
		ret++;
	}
	return (i);
}

int	err_free1(char *s1)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (-1);
}

int	err_free2(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (-1);
}
