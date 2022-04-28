/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:20 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/27 20:47:59 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_arg	*init_arg(char **envp)
{
	t_arg	*arg;

	arg = (t_arg *)ft_calloc(1, sizeof(t_arg));
	if (arg == 0)
		return (0);
	arg->env = init_env(envp);
	arg->envp = envp;
	return (arg);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	char	**temp;
	int		i;

	i = 0;
	current = 0;
	head = 0;
	while (envp[i] != 0)
	{
		temp = ft_split(envp[i], '=');
		if (temp == 0)
		{
			free_env(head);
			return (0);
		}
		if (!add_env(&head, &current, &i))
			return (0);
		current->key = temp[0];
		current->value = temp[1];
		free(temp);
		temp = 0;
		i++;
	}
	return (head);
}

int	add_env(t_env **head, t_env **current, int *i)
{
	if (*i != 0)
	{
		(*current)->next = (t_env *)ft_calloc(1, sizeof(t_env));
		if ((*current) == 0)
		{
			free_env((*head));
			return (0);
		}
		(*current) = (*current)->next;
	}
	else
	{
		(*current) = (t_env *)ft_calloc(1, sizeof(t_env));
		if ((*current) == 0)
		{
			free((*current));
			return (0);
		}
		(*head) = (*current);
	}
	return (1);
}

char	*get_env(t_env *env_head, char *key)
{
	char	*output;
	int		i;

	i = 0;
	while (env_head != 0)
	{
		if (ft_strcmp(env_head->key, key) == 0)
		{
			output = ft_strdup(env_head->value);
			if (output == 0)
				return("error");
			return (output);
		}
		env_head = env_head->next;
	}
			printf("if\n");
	return (0);
}
