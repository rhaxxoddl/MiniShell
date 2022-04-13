/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:33:57 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/13 20:04:44 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "parsing.h"

char	*s_quotes(char **line)
{
	int		i;
	char	*output;

	i = 0;
	while ((*line)[i] != '\'')
		i++;
	if (i == 0)
		return (0);
	output = ft_substr((*line), 0, i);
	*line = (*line) + i + 1;
	return (output);
}

// char	*pro_quotes(char *line)
// {
// 	int		i;

// 	i = 0;
// 	if (check_quotes(line) == 0)
// 		return (0);
// 	while (line[i] != 0)
// 	{
		
// 	}
// }

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