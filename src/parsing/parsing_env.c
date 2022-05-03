/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:10:02 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/03 19:34:21 by sanjeon          ###   ########.fr       */
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

void	pro_env(char **envp, char **temp, char **line, int *i)
{
	char	*env;

	pro_before_str(temp, line, i);
	(*line)++;
	env = trans_env(envp, line);
	if (env == 0)
		ft_error();
	*temp = app_str(*temp, env);
	if (*temp == 0)
		ft_error();
}

char	*trans_env(char **envp, char **line)
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
	if (temp == 0)
		return (0);
	j = 0;
	output = get_env(envp, temp);
	free(temp);
	if (output == 0)
		return (0);
	*line = &(*line)[i];
	return (output);
}
