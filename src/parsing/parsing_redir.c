/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:25:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/22 13:22:40 by sanjeon          ###   ########.fr       */
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
				redir_head = pro_redir(line, env_head, get_redir_type((*line) + i));
				printf("if\n");
				if (redir_head == 0)
					return (0);
				current = redir_head;
			}
			else
			{
				current->next = pro_redir(line, env_head, get_redir_type((*line) + i));
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

t_redir	*pro_redir(char **line, t_env *env_head, int redir_type)
{
	t_redir	*redir;
	char	*temp;
	int		l;

	l = 1;
	temp = 0;
	while (ft_isspace(**line))
		(*line)++;
	printf("in redir : %s\n", *line);
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (redir == 0)
		return (0);
	if (valid_dol(&(*line)[l]))
	{
		if (!pro_env(&temp, line, env_head, &l))
			return (0);
	}
	else if ((*line)[l] == '\'')
	{
		if (!pro_s_quotes(&temp, line, &l))
			return (0);
	}
	else if ((*line)[l] == '\"')
	{
		if (!pro_d_quotes(&temp, line, env_head, &l))
			return (0);
	}
	ft_memset(*line, ' ', l);
	printf("temp : \"%s\"\n", *line);
	redir->filename = temp;
	redir->redir_type = redir_type;
	if (*line[l] != 0)
		(*line) = (*line) + l + 1;
	return (redir);
}
