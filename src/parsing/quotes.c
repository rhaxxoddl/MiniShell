/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:33:57 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/18 13:41:52 by sanjeon          ###   ########.fr       */
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
	if (output == 0)
		return ("error");
	*line = (*line) + i + 1;
	return (output);
}

char	*d_quotes(char **line, char **envp)
{
	int		i;
	char	*output;

	i = 0;
	output = 0;
	while ((*line)[i] != '\"' && (*line)[i] != 0)
	{
		if ((*line)[i] == '$')
		{
			output = app_str(output, ft_substr(*line, 0, i));
			if (output == 0)
				return ("error");
			*line = (*line) + i + 1;
			i = 0;
			output = app_str(output, pro_env(line, envp));
		}
		else
			i++;
	}
	if ((*line)[i] == 0)
		return ("error");
	output = app_str(output, ft_substr(*line, 0, i));
	if (output == 0)
		return ("error");
	*line = (*line) + i + 1;
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