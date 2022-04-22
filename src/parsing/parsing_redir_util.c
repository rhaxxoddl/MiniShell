/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:02:18 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/22 15:02:47 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	pro_d_quotes_r(char **temp, char **line, t_env *env_head, int *i)
{
	if (*temp == 0)
		*temp = ft_substr((*line), 0, *i);
	else
		*temp = app_str(*temp, ft_substr(*line, 0, *i));
	if (*temp == 0)
		return (0);
	(*line) = (*line) + (*i) + 1;
	*i = 0;
	*temp = app_str(*temp, d_quotes(line, env_head));
	if ((*temp) == 0)
		return (0);
	return (1);
}

int	pro_s_quotes_r(char **temp, char **line, int *i)
{
	if (*temp == 0)
		*temp = ft_substr((*line), 0, *i);
	else
		*temp = app_str(*temp, ft_substr(*line, 0, *i));
	if (*temp == 0)
		return (0);
	(*line) = (*line) + (*i) + 1;
	*i = 0;
	*temp = app_str(*temp, s_quotes(line));
	if ((*temp) == 0)
		return (0);
	return (1);
}

char	*s_quotes_r(char **line)
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

char	*d_quotes_r(char **line, t_env *env_head)
{
	int		i;
	char	*output;

	i = 0;
	output = 0;
	while ((*line)[i] != '\"' && (*line)[i] != 0)
	{
		if (valid_dol(&(*line)[i]))
		{
			if (!pro_env(&output, line, env_head, &i))
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
