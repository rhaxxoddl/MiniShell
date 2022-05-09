/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:51 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/03 19:35:59 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

int	end_main(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[11C", 1);
	ft_putstrendl_fd("exit", 1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	(void)argc;
	t_arg	*arg;
	char    *line;

	arg = 0;
	sig_init();
	arg = init_arg(envp);
	if (arg == 0)
		ft_error();
	while(1)
	{
		line = readline("minishell$ ");
		add_history(line);
		if (line == NULL)
			return (end_main());
		arg->cmd_arg = parsing(arg->envp, line);
		// print_arg(arg->cmd_arg);
		if (line != 0)
			free(line);
		if (arg->cmd_arg->cmd_count != 0)
			run_process(arg, arg->cmd_arg);
//		system("leaks minishell");
	}
}
