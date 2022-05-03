/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:33:57 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/03 10:16:02 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_arg(t_cmd_arg *arg)
{
	t_cmd	*temp_cmd;
	t_redir * temp_redir;

	temp_cmd = arg->cmd_head;
	while (temp_cmd != 0)
	{
		temp_redir = temp_cmd->redir;
		for (int i = 0; temp_cmd->cmd_param[i] != 0; i++)
			printf("[%d]cmd->cmd_param[%d] : \"%s\"\n", temp_cmd->cmd_idx, i, temp_cmd->cmd_param[i]);
		while (temp_redir != 0)
		{
			printf("[%p]file : %s, type : %d\n", temp_redir, temp_redir->filename, temp_redir->redir_type);
			temp_redir = temp_redir->next;
		}
		temp_cmd = temp_cmd->next;
	}
}

char	*app_str(char *dest, char *src)
{
	char	*output;

	output = 0;
	if (src == 0)
		return (0);
	if (dest != 0 && *dest != 0)
	{
		if (src != 0 && *src != 0)
			output = ft_strjoin(dest, src);
		else
			return (dest);
	}
	else if (src != 0 && *src != 0)
		output = ft_strdup(src);
	if (output == 0)
		ft_error();
	if (dest != 0)
	{
		free(dest);
		dest = 0;
	}
	free(src);
	src = 0;
	return (output);
}

char	**add_col(char **cmd, char **add)
{
	int		l;
	int		i;
	char	**temp;

	l = 0;
	while (cmd[l] != 0)
		l++;
	temp = (char **)ft_calloc(l + 2, sizeof(char *));
	if (temp == 0)
		ft_error();
	i = -1;
	while (++i < l)
		temp[i] = cmd[i];
	temp[i] = *add;
	*add = 0;
	free(*add);
	free(cmd);
	return (temp);
}

void	pro_before_str(char **temp, char **line, int *i)
{
	char	*add_temp;

	if (*i <= 0)
		return ;
	add_temp = ft_substr(*line, 0, *i);
	if (add_temp == 0)
		ft_error();
	*temp = app_str(*temp, add_temp);
	if (*temp == 0)
		ft_error();
	else if (add_temp != 0 && *add_temp == 0)
		free(add_temp);
	(*line) = (*line) + *i;
	*i = 0;
}
