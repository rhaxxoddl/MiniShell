/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:45 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/03 19:34:44 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	pro_d_quotes(char **envp, char **temp, char **line, int *i)
{
	char	*d_quotes_temp;

	pro_before_str(temp, line, i);
	(*line)++;
	d_quotes_temp = d_quotes(envp, line);
	*temp = app_str(*temp, d_quotes_temp);
	if ((*temp) == 0)
		ft_error();
}

void	pro_s_quotes(char **temp, char **line, int *i)
{
	char	*s_quotes_temp;

	pro_before_str(temp, line, i);
	(*line)++;
	s_quotes_temp = s_quotes(line);
	if (s_quotes_temp == 0)
		ft_error();
	*temp = app_str(*temp, s_quotes_temp);
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
	if ((*line)[i] == 0)
		ft_str_error("ERROR : incorrect quotes");
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
	char	*temp;

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
		ft_str_error("ERROR : incorrect quotes");
	temp = ft_substr(*line, 0, i);
	if (temp == 0)
		ft_error();
	output = app_str(output, temp);
	if (output == 0)
		ft_error();
	*line = (*line) + i + 1;
	return (output);
}
