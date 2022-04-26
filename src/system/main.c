/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:51 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/26 17:34:40 by sanjeon          ###   ########.fr       */
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
		if (line == NULL)
			return (1);
		arg->cmd_arg = parsing(line, envp);
		print_arg(arg->cmd_arg);
		free(line);
		if (arg->cmd_arg->cmd_count != 0)
			run_process(arg, arg->cmd_arg);
	}
	return (0);
}
