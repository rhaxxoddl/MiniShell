/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:00:39 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/22 20:57:28 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

t_cmd_list	*create_cmd_list(int argc, char *argv[], t_arg *arg)
{
	int			i;
	t_cmd_list	*head;
	t_cmd_list	*temp;

	i = 2;
	head = add_cmd_list(argv[i], arg->path, i - 2);
	i++;
	if (head == 0)
		p_a_error(arg);
	temp = head;
	while (i < argc - 1)
	{
		temp->next = add_cmd_list(argv[i], arg->path, i - 2);
		if (temp->next == 0)
			p_a_error(arg);
		temp = temp->next;
		i++;
	}
	arg->cmd_count = i - 2;
	return (head);
}

t_cmd_list	*add_cmd_list(char *cmd_str, char *path[], int	cmd_idx)
{
	t_cmd_list	*temp;

	temp = (t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list));
	if (temp == 0)
		return (0);
	temp->cmd_with_option = (char **)ft_split(cmd_str, ' ');
	if (temp->cmd_with_option == 0)
		return (0);
	temp->cmd = (char *)ft_strdup(temp->cmd_with_option[0]);
	if (temp->cmd == 0)
		return (0);
	temp->cmd_path = cmd_connect_path(temp->cmd, path);
	if (temp->cmd_path == 0)
		return (0);
	temp->cmd_idx = cmd_idx;
	return (temp);
}

// This function is to search the paths
// and create a string that combines the path
// where the command file is located and the command.
// If the file path is not found, only the command is returned.
char	*cmd_connect_path(char *cmd, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	temp = 0;
	while (path[i] != 0)
	{
		temp = ft_strjoin(path[i], cmd);
		if (temp == 0)
			return (0);
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
		temp = 0;
		i++;
	}
	temp = ft_strdup(cmd);
	if (temp == 0)
		return (0);
	return (temp);
}
