/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:33:57 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/11 20:00:07 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "parsing.h"

char	*pro_quotes(char *str)
{
	int		*c_flag;
	int		i;

	i = 0;
	c_flag = (int *)ft_calloc(ft_strlen(str) + 1, sizeof(int));
	while (str[i] != 0)
	{
		if (str[i] == '\'')
		{
			single_quote(str, c_flag);
			while (str[i] != '\'' && str[i] != 0)
				i++;
		}
		else if (str[i] == '\"')
		{
			double_quote(str, c_flag);
			while (str[i] != '\"' && str[i] != 0)
				i++;
		}
		i++;
	}
}

char	*app_str(char *dest, char *src)
{
	char	*output;

	output = 0;
	if (dest != 0)
		output = ft_strjoin(dest, src);
	else
		output = ft_strdup(src);
	if (output != 0)
	{
		if (dest != 0)
			free(dest);
		if (src != 0)
			free(src);
	}
	return (output);
}

int		check_quotes(char *line)
{
	char	*next_quotes;

	next_quotes = 0;
	while (line != 0)
	{
		if (*line == '\'')
		{
			next_quotes = ft_strchr(++line, '\'');
			if (next_quotes != 0)
				line = next_quotes;
			else
				return (0);
		}
		if (*line == '\"')
		{
			next_quotes = ft_strchr(++line, '\"');
			if (next_quotes != 0)
				line = next_quotes;
			else
				return (0);
		}
		line++;
	}
	return (1);
}

// char	*double_quote(char *str, int *c_flag)
// {
// 	// ft_strchr(str, )
// }