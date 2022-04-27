/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:25:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/27 16:58:15 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing_redir(t_cmd *cmd, char **line, int *i)
{
	printf("[%p]parsing_redir : %s\n", *line, *line);
	if (cmd->redir == 0)
		cmd->redir = pro_redir(line, get_redir_type(*line), i);
	else
	{
		cmd->redir->next = pro_redir(line, get_redir_type(*line), i);
	}
	if (cmd->redir == 0)
		return (0);
	printf("[%p]before space\n", *line);
	while (ft_isspace(**line))
		(*line)++;
	printf("[%p]out parsing_redir\n", *line);
	return (1);
}

int	get_redir_type(char *c)
{
	if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (HERE_DOC);
		return (REDIR_IN);
	}
	else if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (REDIR_APP);
		return (REDIR_OUT);
	}
	else
		return (0);
}

t_redir	*pro_redir(char **line, int redir_type, int *i)
{
	printf("[%p]in pro_redir : %s\n", *line, *line);
	t_redir	*redir;
	char	*temp;

	temp = 0;
	while (**line == '<' || **line == '>')
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (redir == 0)
		return (0);
	while ((*line)[*i] != 0 && !ft_isspace((*line)[*i])
			&& !get_redir_type(&(*line)[*i]))
	{
		if (valid_dol(&(*line)[*i]))
		{
			if (!pro_env(&temp, line, i))
				return (0);
		}
		else if ((*line)[*i] == '\'')
		{
			if (!pro_s_quotes(&temp, line, i))
				return (0);
		}
		else if ((*line)[*i] == '\"')
		{
			if (!pro_d_quotes(&temp, line, i))
				return (0);
		}
		else
			(*i)++;
	}
	printf("hihi\n");
	temp = app_str(temp, ft_substr(*line, 0, *i));
	redir->filename = temp;
	redir->redir_type = redir_type;
	printf("i : %d\n", *i);
	(*line) = (*line) + *i + 1;
	printf("[%p]out pro_redir : %s\nout temp : %s\n", *line, *line, temp);
	*i = 0;
	return (redir);
}
