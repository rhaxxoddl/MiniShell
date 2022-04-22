/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:25:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/22 16:09:04 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redir	*parsing_redir(char **line, t_env *env_head)
{
	t_redir	*redir_head;
	t_redir	*current;
	int		i;

	i = 0;
	redir_head = 0;
	while ((*line)[i] != 0 && (*line)[i] != '|')
	{
		if (get_redir_type((*line) + i))
		{
			if (redir_head == 0)
			{
				redir_head = pro_redir(line, env_head, get_redir_type((*line) + i), &i);
				printf("if\n");
				if (redir_head == 0)
					return (0);
				current = redir_head;
			}
			else
			{
				current->next = pro_redir(line, env_head, get_redir_type((*line) + i), &i);
				current = current->next;
			}
		}
		else
			i++;
	}
	return (redir_head);
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

t_redir	*pro_redir(char **line, t_env *env_head, int redir_type, int *i)
{
	t_redir	*redir;
	char	*temp;

	temp = 0;
	while (ft_isspace(**line))
		(*line)++;
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (redir == 0)
		return (0);
	while (&(*line)[*i] != 0 && !ft_isspace((*line)[*i]))
	{
		if (valid_dol(&(*line)[*i]))
		{
			if (!pro_env(&temp, line, env_head, i))
				return (0);
		}
		else if ((*line)[*i] == '\'')
		{
			if (!pro_s_quotes(&temp, line, i))
				return (0);
		}
		else if ((*line)[*i] == '\"')
		{
			if (!pro_d_quotes(&temp, line, env_head, i))
				return (0);
		}
		else
			(*i)++;
	}
	temp = app_str(temp, ft_substr(*line, 0, *i));
	redir->filename = temp;
	redir->redir_type = redir_type;
	if (*line[*i] != 0)
		(*line) = (*line) + *i + 1;
	*i = 0;
	return (redir);
}
