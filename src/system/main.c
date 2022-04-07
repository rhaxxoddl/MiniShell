/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:51 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/07 20:53:53 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <readline/readline.h>
#include <readline/history.h>

static void 	parsing(t_arg *arg, char *envp[])
{
	arg->c_t = ft_calloc(2, sizeof(t_cmd));
	arg->c_t[0].cmd = ft_calloc(3, sizeof(char *));
	arg->c_t[0].cmd[0] = ft_strdup("/usr/bin/grep");
	arg->c_t[0].cmd[1] = ft_strdup("d");
	arg->c_t[0].redir = ft_calloc(1, sizeof(t_redir));
	arg->c_t[0].redir->redir_type = HERE_DOC;
	arg->c_t[0].redir->filename = ft_strdup("a");
	arg->c_t[0].redir->next = 0;
	// arg->c_t[1].cmd = ft_calloc(2, sizeof(char *));
	// arg->c_t[1].cmd[0] = ft_strdup("/bin/cat");
	// arg->c_t[1].redir = ft_calloc(1, sizeof(t_redir));
	// arg->c_t[1].redir->redir_type = REDIR_OUT;
	// arg->c_t[1].redir->filename = ft_strdup("b");
	
	arg->cmd_count = 1;
	arg->cmd_idx = 0;
	arg->fds = malloc_fds(arg->cmd_count);
	arg->envp = envp;
	arg->std_in = dup(STDIN_FILENO);
	arg->std_out = dup(STDOUT_FILENO);
	arg->status = 100;
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	(void)argc;
	t_arg	*arg;
	char    *line;

	sig_init();
	while(1)
	{
		line = readline("minishell$ ");
		add_history(line);
		if (line == NULL)
			return (1);
		printf("str: %s\n", line);
		free(line);
	}
	arg = init_arg();
	parsing(arg, envp);
	while (arg->cmd_idx < arg->cmd_count)
	{
		run_cmd(arg, arg->cmd_idx);
		arg->cmd_idx++;
	}
	return (0);
}
