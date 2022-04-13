/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:38:13 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/13 19:14:40 by sanjeon          ###   ########.fr       */
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
	int	i;

	i = 0;
	temp = 0;
	while ((*line)[i] != 0 && (*line)[i] != '|')
	{
		if ((*line)[i] == '$')
		{
			printf("i : %d\n", i);
			if (temp == 0)
				temp = ft_substr((*line), 0, i);
			else
				temp = app_str(temp, ft_substr((*line), 0, i));
			(*line) = &(*line)[++i];
			i = 0;
			temp = app_str(temp, pro_env(line, envp));
		}
		else if ((*line)[i] == '\'')
		{
			// *line[i] 전까지 temp에 담기 
			// temp = app_str(temp, s_quotes(*line));
		}
		else if ((*line)[i] == '\"')
		{
			// *line[i] 전까지 temp에 담기 
			// temp = app_str(temp, d_quotes(*line));

		}
		i++;
	}
	temp = app_str(temp, ft_substr((*line), 0, i - 1));
	// cmd = add_cmd(temp);
	cmd = 0;
	free(temp);
	return (cmd);
}

char	*pro_env(char **line, char **envp)
{
	char	*output;
	int		i;
	int		j;

	i = 0;
	while (ft_isalnum((*line)[i]) && ft_isalpha((*line)[i]))
		i++;
	if (i == 0)
		return (0);
	j = 0;
	while (ft_strncmp((*line), envp[j], i) != 0)
		j++;
	output = ft_strdup((envp[j] + i + 1));
	*line = &(*line)[i];
	return (output);
}

char	*app_str(char *dest, char *src)
{
	char	*output;

	output = 0;
	if (dest != 0)
		output = ft_strjoin(dest, src);
	else
		output = ft_strdup(src);
	if (output != 0)
	{
		if (dest != 0)
			free(dest);
		if (src != 0)
			free(src);
	}
	return (output);
}
