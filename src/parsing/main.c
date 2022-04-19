/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:44:48 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/19 08:59:24 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

t_env	*get_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	char	**temp;
	int		i;

	i = 0;
	while (envp[i] != 0)
	{
		printf("hihi\n");
		temp = ft_split(envp[i], '=');
		if (temp == 0)
		{
			free_env(head);
			return (0);
		}
		if (i != 0)
		{
			current->next = (t_env *)ft_calloc(1, sizeof(t_env));
			if (current == 0)
			{
				free_env(head);
				return (0);
			}
			current = current->next;
		}
		else
		{
			current = (t_env *)ft_calloc(1, sizeof(t_env));
			if (current == 0)
				free(current);
			head = current;
		}
		current->key = temp[0];
		current->value = temp[1];
		free(temp);
		temp = 0;
		i++;
	}
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	char	*str = ft_strdup("\'abcd$PATH\' pad$PATH");

	env = get_env(envp);
	printf("str : %s\n", str);
	parsing_split(&str, env);
	return (0);
}