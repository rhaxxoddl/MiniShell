/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:33:57 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/27 17:13:49 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_arg(t_cmd_arg *arg)
{
	t_cmd	*temp_cmd;

	temp_cmd = arg->cmd_head;
	while (temp_cmd != 0)
	{
		for (int i = 0; temp_cmd->cmd_param[i] != 0; i++)
			printf("[%d]cmd->cmd_param[%d] : \"%s\"\n", temp_cmd->cmd_idx, i, temp_cmd->cmd_param[i]);
		while (temp_cmd->redir != 0)
		{
			printf("[%p]file : %s, type : %d\n", temp_cmd->redir, temp_cmd->redir->filename, temp_cmd->redir->redir_type);
			temp_cmd->redir = temp_cmd->redir->next;
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
	printf("[%p]dest : \"%s\"\n[%p]src : \"%s\"\n", dest, dest, src, src);
	while (ft_isspace(*src))
		src++;
	if (dest != 0 && *dest != 0)
	{
		if (src != 0 && *src != 0)
			output = ft_strjoin(dest, src);
		else
			return (dest);
	}
	else if (src != 0 && *src != 0)
	{
		output = ft_strdup(src);
		printf("hihi\n");
	}
	if (dest != 0)
	{
		free(dest);
		dest = 0;
	}
	if (src != 0)
	{
		free(src);
		printf("free\n");
		src = 0;
	}
		printf("output : %s\n", output);
	return (output);
}

char	**add_col(char **cmd, char *add)
{
	printf("add_cal\n");
	int		l;
	int		i;
	char	**temp;

	l = 0;
	while (cmd[l] != 0)
		l++;
	printf("in add_cal l : %d\n", l);
	temp = (char **)ft_calloc(l + 2, sizeof(char *));
	if (temp == 0)
		return (0);
	i = -1;
	while (++i < l)
		temp[i] = cmd[i];
	temp[i] = add;
	free(cmd);
	printf("out add_col : %s\n", add);
	return (temp);
}


int	pro_before_str(char **temp, char **line, int *i)
{
	char	*add_temp;

	if (*i <= 0)
		return (1);
	add_temp = ft_substr(*line, 0, *i);
	if (add_temp == 0)
		return (0);
	printf("temp : %p\nadd_temp : %s\nline : %s\n", *temp, add_temp, *line);
	if (temp != 0 && *temp != 0)
	{
		printf("in\n");
		*temp = app_str(*temp, add_temp);
		if (*temp == 0)
			return (0);
		printf("2=================\n");
		printf("[%p]temp[%d] : %s\n", *temp, *i, *temp);
		printf("[%p]line[%d] : %s\n", *line, *i, *line);
		printf("2=================\n");
	}
	else if (add_temp != 0 && *add_temp == 0)
		free(add_temp);
	(*line) = (*line) + *i;
	*i = 0;
	return (1);
}