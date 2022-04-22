/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:10:02 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/22 16:51:56 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	valid_dol(char *line)
{
	if (*line == '$')
	{
		line++;
		if (ft_isalnum(*line) || (*line) == '_')
			return (1);
		else if ((*line) == '?')
			return (2); // 나중에 $? 이거 부르는 함수로 변환
	}
	return (0);
}

int	pro_env(char **temp, char **line, t_env *env_head, int *i)
{
	if (!pro_before_str(temp, line, i))
		return (0);
	(*line)++;
	*temp = app_str(*temp, trans_env(line, env_head));
	if ((*temp) == 0)
		return (0);
	return (1);
}

char	*trans_env(char **line, t_env *env_head)
{
	char	*output;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		i++;
	if (i == 0)
	{
		output = ft_strdup("$");
		return (output);
	}
	temp = ft_substr(*line, 0, i);
	j = 0;
	while (env_head != 0 && ft_strcmp(temp, env_head->key) != 0)
		env_head = env_head->next;
	if (env_head != 0)
		output = ft_strdup((env_head->value));
	else
		output = 0;
	*line = &(*line)[i];
	return (output);
}