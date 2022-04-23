/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:37:54 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/23 16:23:41 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd_arg	*parsing(char *line, char **envp)
{
	t_cmd_arg	*cmd_arg;
	t_cmd		*temp_cmd;
	int		i;

	cmd_arg = (t_cmd_arg *)ft_calloc(1, sizeof(t_cmd_arg));
	if (cmd_arg == 0)
		return (0);
	while (ft_isspace(*line))
		line++;
	i = -1;
	while (line[++i] != 0)
	{
		if (i == 0)
		{
			temp_cmd = parsing_cmd(&line);
			cmd_arg->cmd_head = temp_cmd;
			cmd_arg->cmd_count = 1;
			temp_cmd->cmd_idx = 0;
		}
		else
		{
			temp_cmd->next = parsing_cmd(&line);
			temp_cmd = temp_cmd->next;
			cmd_arg->cmd_count++;
			temp_cmd->cmd_idx = cmd_arg->cmd_count - 1;
		}
	}
	cmd_arg->fds = malloc_fds(cmd_arg->cmd_count);
	if (cmd_arg->fds == 0)
		return (0);
	cmd_arg->path = get_path(envp);
	return (cmd_arg);
}

t_cmd	*parsing_cmd(char **line)
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
			if (!pro_env(&temp, line, &i))
				return (0);
		}
		else if ((*line)[i] == '\'')
		{
			if (!pro_s_quotes(&temp, line, &i))
				return (0);
		}
		else if ((*line)[i] == '\"')
		{
			if (!pro_d_quotes(&temp, line, &i))
				return (0);
		}
		else if (get_redir_type(&(*line)[i]))
		{
			if (!pro_before_str(&temp, line, &i) ||
				!parsing_redir(cmd, line, &i))
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
