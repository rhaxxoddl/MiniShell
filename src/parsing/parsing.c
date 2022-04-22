/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:37:54 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/22 17:07:09 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_arg	*parsing(char *line, t_env *env_head)
{
	t_arg	*arg;
	t_cmd	*temp_cmd;
	int		i;

	arg = (t_arg *)ft_calloc(1, sizeof(t_arg));
	if (arg == 0)
		return (0);
	while (ft_isspace(*line))
		line++;
	i = -1;
	while (line[++i] != 0)
	{
		if (i == 0)
		{
			temp_cmd = parsing_cmd(&line, env_head);
			arg->c_t = temp_cmd;
		}
		else
		{
			temp_cmd->next = parsing_cmd(&line, env_head);
			temp_cmd = temp_cmd->next;
		}
	}
	return (arg);
}

t_cmd	*parsing_cmd(char **line, t_env *env_head)
{
	t_cmd	*cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = 0;
	while (ft_isspace(**line))
		(*line)++;
	// 여기부터
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (cmd == 0)
		return (0);
	cmd->cmd_param = (char **)ft_calloc(1, sizeof(char *));
	if (cmd->cmd_param == 0)
		return (0); // 전에 할당한 거 해제해야 함.
	cmd->redir = 0;
	// 여기까지 함수로 빼기
	while ((*line)[i] != 0 && (*line)[i] != '|')
	{
		if (valid_dol(&(*line)[i]))
		{
			if (!pro_env(&temp, line, env_head, &i))
				return (0);
		}
		else if ((*line)[i] == '\'')
		{
			if (!pro_s_quotes(&temp, line, &i))
				return (0);
		}
		else if ((*line)[i] == '\"')
		{
			if (!pro_d_quotes(&temp, line, env_head, &i))
				return (0);
		}
		else if (get_redir_type(&(*line)[i]))
		{
			if (!pro_before_str(&temp, line, &i) ||
				!parsing_redir(cmd, line, env_head, &i))
				return (0);
		}
		else if (ft_isspace((*line)[i]))
		{
			temp = app_str(temp, ft_substr(*line, 0, i));
			cmd->cmd_param = add_col(cmd->cmd_param, temp);
			temp = 0;
			(*line) = (*line) + i;
			while (ft_isspace(**line))
				(*line)++;
			i = 0;
		}
		else
			i++;
	}
	if (i > 0 && !ft_isspace((*line)[i - 1]))
	{
		temp = app_str(temp, ft_substr(*line, 0, i));
		if (temp == 0)
			return (0);
		cmd->cmd_param = add_col(cmd->cmd_param, temp);
		if (cmd->cmd_param == 0)
			return (0);
		temp = 0;
	}
	if (*line[i] != 0)
		(*line) = (*line) + i + 1;
	return (cmd);
}
