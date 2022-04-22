/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:51 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/22 21:41:13 by sanjeon          ###   ########.fr       */
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
	t_env	*env;
	char    *line;

	env = 0;
	arg = 0;
	sig_init();
	env = get_env(envp);
	if (env == 0)
		return (0);
	while(1)
	{
		line = readline("minishell$ ");
		add_history(line);
		if (line == NULL)
			return (1);
		arg = parsing(line, env);
		run_cmd(arg, arg->cmd_idx, env);
		// printf("str: %s\n", line);
		free(line);
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
