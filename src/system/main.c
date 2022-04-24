/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:51 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/24 17:38:04 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	(void)argc;
	t_arg	*arg;
	char    *line;

	arg = 0;
	// sig_init();
	arg = init_arg(envp);
	if (arg == 0)
		return (0);
	while(1)
	{
		line = readline("minishell$ ");
		add_history(line);
		if (line == NULL) {
			return (1);
		}
		arg->cmd_arg = parsing(line, envp);
		free(line);
		if (arg->cmd_arg->cmd_count != 0)
			run_process(arg, arg->cmd_arg);
	}
	// arg = init_arg();
	// parsing(arg, envp);
	// while (arg->cmd_idx < arg->cmd_count)
	// {
	// 	run_cmd(arg, arg->cmd_idx);
	// 	arg->cmd_idx++;
	// }
	return (0);
}
