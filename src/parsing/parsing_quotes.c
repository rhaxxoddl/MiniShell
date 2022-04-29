/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:45 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/29 10:25:30 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	pro_d_quotes(char **envp, char **temp, char **line, int *i)
{
	pro_before_str(temp, line, i);
	(*line)++;
	*temp = app_str(*temp, d_quotes(envp, line));
	if ((*temp) == 0)
		ft_error();
}

void	pro_s_quotes(char **temp, char **line, int *i)
{
	pro_before_str(temp, line, i);
	(*line)++;
	*temp = app_str(*temp, s_quotes(line));
	if ((*temp) == 0)
		ft_error();
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
		ft_error();
	*line = (*line) + i + 1;
	return (output);
}

char	*d_quotes(char **envp, char **line)
{
	int		i;
	char	*output;

	i = 0;
	output = 0;
	while ((*line)[i] != '\"' && (*line)[i] != 0)
	{
		if (valid_dol(&(*line)[i]))
			pro_env(envp, &output, line, &i);
		else
			i++;
	}
	if ((*line)[i] == 0)
		return ("Error with odd quotation marks");
	output = app_str(output, ft_substr(*line, 0, i));
	*line = (*line) + i + 1;
	return (output);
}
