/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:51 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/24 20:44:39 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void 	parsing(t_arg *arg, char *envp[])
{
	arg->c_t = ft_calloc(2, sizeof(t_cmd));
	arg->c_t[0].cmd = ft_calloc(3, sizeof(char *));
	arg->c_t[0].cmd[0] = ft_strdup("/bin/echo");
	arg->c_t[0].cmd[1] = ft_strdup("42");
	
	arg->c_t[1].cmd = ft_calloc(2, sizeof(char *));
	arg->c_t[1].cmd[0] = ft_strdup("/bin/cat");
	
	arg->cmd_count = 2;
	arg->cmd_idx = 0;
	arg->fds = malloc_fds(arg->cmd_count);
	arg->envp = envp;
	arg->std_in = dup(STDIN_FILENO);
	arg->std_out = dup(STDOUT_FILENO);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	(void)argc;
	t_arg		*arg;

	arg = init_arg();
	parsing(arg, envp);
	while (arg->cmd_idx < arg->cmd_count)
	{
		ft_pipe(arg, arg->cmd_idx);
		arg->cmd_idx++;
	}
	return (0);
}
