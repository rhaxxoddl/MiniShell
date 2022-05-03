/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:25:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/03 10:15:31 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing_redir(char **envp, t_cmd *cmd, char **line, int *i)
{
	if (cmd->redir == 0)
		cmd->redir = pro_redir(envp, line, get_redir_type(*line), i);
	else
		cmd->redir->next = pro_redir(envp, line, get_redir_type(*line), i);
	if (cmd->redir == 0)
		ft_error();
	while (ft_isspace(**line))
		(*line)++;
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

t_redir	*pro_redir(char **envp, char **line, int redir_type, int *i)
{
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
		pro_switch(line, i, &temp, envp);
		// if (valid_dol(&(*line)[*i]))
		// 	pro_env(envp, &temp, line, i);
		// else if ((*line)[*i] == '\'')
		// 	pro_s_quotes(&temp, line, i);
		// else if ((*line)[*i] == '\"')
		// 	pro_d_quotes(envp, &temp, line, i);
		// else
		// 	(*i)++;
	}
	temp = app_str(temp, ft_substr(*line, 0, *i));
	redir->filename = temp;
	redir->redir_type = redir_type;
	(*line) = (*line) + *i + 1;
	*i = 0;
	return (redir);
}

void	pro_switch(char **line, int *i, char **temp, char **envp)
{
	if (valid_dol(&(*line)[*i]))
		pro_env(envp, temp, line, i);
	else if ((*line)[*i] == '\'')
		pro_s_quotes(temp, line, i);
	else if ((*line)[*i] == '\"')
		pro_d_quotes(envp, temp, line, i);
	else
		(*i)++;
}
