/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:10:02 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/09 16:03:29 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	valid_dol(char *line)
{
	if (*line == '$')
	{
		line++;
		if (ft_isalnum(*line) || (*line) == '_' || (*line) == '?')
			return (1);
	}
	return (0);
}

void	pro_env(char **envp, char **temp, char **line, int *i)
{
	char	*env;

	pro_before_str(temp, line, i);
	(*line)++;
	env = trans_env(envp, line);
	if (env == 0)
		return ;
	*temp = app_str(*temp, env);
	if (*temp == 0)
		ft_error();
}

static void	count_env_length(char **line, int *i)
{
	while (ft_isalnum((*line)[*i]) || (*line)[*i] == '_' || (*line)[*i] == '?')
	{
		(*i)++;
		if ((*line)[(*i) - 1] == '?')
			break ;
	}
}

char	*trans_env(char **envp, char **line)
{
	char	*output;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	count_env_length(line, &i);
	if (i == 0)
	{
		output = ft_strdup("$");
		return (output);
	}
	temp = ft_substr(*line, 0, i);
	if (temp == 0)
		ft_error();
	j = 0;
	output = get_env(envp, temp);
	*line = &(*line)[i];
	free(temp);
	if (output == 0)
		return (0);
	return (output);
}
