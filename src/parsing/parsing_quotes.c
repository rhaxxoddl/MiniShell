/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:45 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/27 19:22:45 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	pro_d_quotes(t_env *env_head, char **temp, char **line, int *i)
{
	if (!pro_before_str(temp, line, i))
		return (0);
	(*line)++;
	*temp = app_str(*temp, d_quotes(env_head, line));
	if ((*temp) == 0)
		return (0);
	return (1);
}

int	pro_s_quotes(char **temp, char **line, int *i)
{
	if (!pro_before_str(temp, line, i))
		return (0);
	(*line)++;
	*temp = app_str(*temp, s_quotes(line));
	if ((*temp) == 0)
		return (0);
	return (1);
}

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

char	*d_quotes(t_env *env_head, char **line)
{
	int		i;
	char	*output;

	i = 0;
	output = 0;
	while ((*line)[i] != '\"' && (*line)[i] != 0)
	{
		if (valid_dol(&(*line)[i]))
		{
			if (!pro_env(env_head, &output, line, &i))
				return ("error");
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
