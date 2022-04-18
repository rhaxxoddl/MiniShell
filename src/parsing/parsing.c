/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:38:13 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/18 17:49:18 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "pipe_struct.h"
#include "libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

t_arg	*parsing(char *line)
{
	t_arg	*arg;
	char	*pointer_line;
	int		i;

	arg = (t_arg *)ft_calloc(1, sizeof(t_arg));
	if (arg == 0)
		return (0);
	i = -1;
	pointer_line = line;
	while (ft_isspace(line[++i]))
		pointer_line = &line[i];
	while (line[++i] != 0)
	{
		// if (ft)
	}
	return (0);
}

t_cmd	*parsing_split(char **line, char **envp)
{
	t_cmd	*cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = 0;
	while ((*line)[i] != 0 && (*line)[i] != '|')
	{
		if (valid_dol(&(*line)[i]))
		{
			if (!pro_env(&temp, line, envp, &i))
				return (0);
		}
		else if ((*line)[i] == '\'')
		{
			if (!pro_s_quotes(&temp, line, &i))
				return (0);
		}
		else if ((*line)[i] == '\"')
		{
			if (!pro_d_quotes(&temp, line, envp, &i))
				return (0);
		}
		else
			i++;
	}
	// 앞에서 '나 " $ 처리한 후부터 | 이나 NULL전까지 남은 문자열 붙이기 (처리한 후 바로 |이나 NULL이 오는 경우도 처리)
	temp = app_str(temp, ft_substr(*line, 0, i));
	printf("temp : %s\n", temp);
	// cmd = add_cmd(temp);
	cmd = 0;
	free(temp);
	return (cmd);
}

/*
$다음에 오는 문자들과 일치하는 env를 찾아야 하는데 포함되는 env까지 찾음.
env를 key값과 value값으로 나눠서 가지고 있고, ft_strcmp를 따로 만들어야 할듯
*/
char	*trans_env(char **line, char **envp)
{
	char	*output;
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
	j = 0;
	while (envp[j] != 0 && ft_strncmp((*line), envp[j], i) != 0)
		j++;
	if (envp[j] != 0)
		output = ft_strdup((envp[j] + i + 1));
	else
		output = 0;
	*line = &(*line)[i];
	return (output);
}

char	*app_str(char *dest, char *src)
{
	char	*output;

	output = 0;
	if (dest != 0)
	{
		if (src != 0)
			output = ft_strjoin(dest, src);
		else
			return (dest);
	}
	else
		output = ft_strdup(src);
	if (dest != 0)
		free(dest);
	if (src != 0)
		free(src);
	return (output);
}

int	pro_d_quotes(char **temp, char **line, char **envp, int *i)
{
	if (*temp == 0)
		*temp = ft_substr((*line), 0, *i);
	else
		*temp = app_str(*temp, ft_substr(*line, 0, *i));
	if (*temp == 0)
		return (0);
	(*line) = (*line) + (*i) + 1;
	*i = 0;
	*temp = app_str(*temp, d_quotes(line, envp));
	if ((*temp) == 0)
		return (0);
	return (1);
}

int	pro_s_quotes(char **temp, char **line, int *i)
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

int	pro_env(char **temp, char **line, char **envp, int *i)
{
	if (*temp == 0)
		*temp = ft_substr((*line), 0, *i);
	else
		*temp = app_str(*temp, ft_substr(*line, 0, *i));
	if (*temp == 0)
		return (0);
	(*line) = (*line) + (*i) + 1;
	*i = 0;
	*temp = app_str(*temp, trans_env(line, envp));
	if ((*temp) == 0)
		return (0);
	return (1);
}
