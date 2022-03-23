/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:51 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/22 20:56:37 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_arg		*arg;
	t_cmd_list	*temp;
	int			i;

	if (argc < 5)
		perror("Too few arguments!");
	if (argc > 5)
		perror("Too many arguments!");
	arg = parsing(argc, argv, envp);
	temp = arg->cmd_list;
	i = -1;
	while (++i < arg->cmd_count)
	{
		ft_pipe(arg, temp);
		temp = temp->next;
	}
	free_arg(arg);
	return (0);
}
