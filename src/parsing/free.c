/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:54 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/23 16:20:08 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	free_env(t_env *head)
{
	t_env	*temp;

	temp = 0;
	while (head != 0)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i] != 0)
	{
		free(path[i]);
		path[i] = 0;
	}
	free(path);
	path = 0;
}
