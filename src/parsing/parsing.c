/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:37:54 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/19 21:05:16 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "pipe_struct.h"
#include "libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

t_arg	*parsing(char *line, t_env *env_head)
{
	t_arg	*arg;
	t_cmd	*temp_cmd;
	char	*pointer_line;
	int		i;

	arg = (t_arg *)ft_calloc(1, sizeof(t_arg));
	if (arg == 0)
		return (0);
	i = -1;
	pointer_line = line;
	while (ft_isspace(line[++i]))
		pointer_line = &line[i];
	temp_cmd = arg->c_t;
	while (line[++i] != 0)
	{
		temp_cmd = parsing_split(&line, env_head);
		temp_cmd = temp_cmd->next;
	}
	while (arg->c_t != 0)
	{
		for (int i = 0; temp_cmd->cmd_param[i] != 0; i++)
			printf("temp_cmd->cmd_param[%d] : %s\n", i, temp_cmd->cmd_param[i]);
		arg->c_t = arg->c_t->next;
	}
	return (0);
}

t_cmd	*parsing_split(char **line, t_env *env_head)
{
	t_cmd	*cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = 0;
	// 여기부터
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (cmd == 0)
		return (0);
	cmd->cmd_param = (char **)ft_calloc(1, sizeof(char *));
	if (cmd->cmd_param == 0)
		return (0); // 전에 할당한 거 해제해야 함.
	cmd->redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (cmd->redir == 0)
		return (0); // 전에 할당한 거 해제해야 함.
	// 여기까지 함수로 빼기
	while ((*line)[i] != 0 && (*line)[i] != '|')
	{
		if (valid_dol(&(*line)[i]))
		{
			if (!pro_env(&temp, line, env_head, &i))
				return (0);
			printf("env temp : %s\n", temp);
		}
		else if ((*line)[i] == '\'')
		{
			if (!pro_s_quotes(&temp, line, &i))
				return (0);
			printf("s_q temp : %s\n", temp);
		}
		else if ((*line)[i] == '\"')
		{
			if (!pro_d_quotes(&temp, line, env_head, &i))
				return (0);
			printf("d_q temp : %s\n", temp);
		}
		else if (ft_isspace((*line)[i]))
		{
			cmd->cmd_param = add_col(cmd->cmd_param, temp);
			printf("space temp : %s\n", temp);
			temp = 0;
			while (ft_isspace((*line)[i]))
				i++;
			(*line) = (*line) + i;
		}
		else
			i++;
		// printf("[%d]line : \"%s\"\n", i, &(*line)[i]);
	}
	// 앞에서 '나 " $ 처리한 후부터 | 이나 NULL전까지 남은 문자열 붙이기 (처리한 후 바로 |이나 NULL이 오는 경우도 처리)
	printf("temp : %s\n", temp);
	temp = app_str(temp, &(*line)[i]);
	printf("2temp : %s\n", temp);
	cmd->cmd_param = add_col(cmd->cmd_param, temp);
	printf("cmd->cmd_param : %s\n", cmd->cmd_param[0]);
	temp = 0;
	while (ft_isspace(*(*line)), *(*line) == '|')
		(*line)++;
	// for (int i = 0; cmd->cmd_param[i] != 0; i++)
	// 	printf("cmd->cmd_param[%d] : %s\n", i, cmd->cmd_param[i]);
	return (cmd);
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
	{
		printf("temp : %s\nenv : %s\n", temp, env_head->key);
		env_head = env_head->next;
	}
	if (env_head != 0)
		output = ft_strdup((env_head->value));
	else
		output = 0;
	*line = &(*line)[i];
	printf("output : %s\n", output);
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

int	pro_d_quotes(char **temp, char **line, t_env *env_head, int *i)
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

int	pro_env(char **temp, char **line, t_env *env_head, int *i)
{
	if (*temp == 0)
		*temp = ft_substr((*line), 0, *i);
	else
		*temp = app_str(*temp, ft_substr(*line, 0, *i));
	if (*temp == 0)
		return (0);
	(*line) = (*line) + (*i) + 1;
	*i = 0;
	// printf("*line : %s\ntrans_env : %s\n", *line, trans_env(line, env_head));
	*temp = app_str(*temp, trans_env(line, env_head));
	if ((*temp) == 0)
		return (0);
	return (1);
}

char	**add_col(char **cmd, char *add)
{
	int		l;
	int		i;
	char	**temp;

	l = 0;
	while (cmd[l] != 0)
		l++;
	temp = (char **)ft_calloc(l + 2, sizeof(char *));
	if (temp == 0)
		return (0);
	i = -1;
	while (++i < l)
		temp[i] = cmd[i];
	temp[i] = add;
	free(cmd);
	return (temp);
}
