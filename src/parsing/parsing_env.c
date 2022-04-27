/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:10:02 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/27 18:00:38 by sanjeon          ###   ########.fr       */
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

int	pro_env(t_env *env_head, char **temp, char **line, int *i)
{
	// printf("1temp : %s\n", *temp);
	if (i <= 0 && !pro_before_str(temp, line, i))
		return (0);
	(*line)++;
	printf("temp : \"%p\"\nline : \"%p\"\n", *temp, *line);
	*temp = app_str(*temp, trans_env(env_head, line));
	if ((*temp) == 0)
		return (0);
	return (1);
}

char	*trans_env(t_env *env_head, char **line)
{
	char	*output;
	char	*temp;
	int		i;
	int		j;

	printf("22222222123 : %p\n", *line);
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
	output = ft_strdup(get_env(env_head, temp));
	free(temp);
	if (output == 0)
		return (0);
	*line = &(*line)[i];
	return (output);
}
