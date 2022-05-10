/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:51 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/10 10:49:44 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

static int	end_main(t_arg *arg)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[11C", 1);
	ft_putstrendl_fd("exit", 1);
	free_str_arr(arg->envp);
	free(arg);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_arg			*arg;
	char			*line;
	struct termios	set;

	(void)argv;
	(void)argc;
	tcgetattr(STDOUT_FILENO, &set);
	set.c_lflag &= (~ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &set);
	arg = 0;
	sig_init();
	arg = init_arg(envp);
	if (arg == 0)
		ft_error();
	while (1)
	{
		line = readline("minishell$ ");
		add_history(line);
		if (line == NULL)
			return (end_main(arg));
		arg->cmd_arg = parsing(arg->envp, line);
		free(line);
		if (arg->cmd_arg->cmd_count != 0)
			run_process(arg, arg->cmd_arg);
	}
}
