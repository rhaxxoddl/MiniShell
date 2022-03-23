/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:40:49 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/22 20:08:53 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

t_arg	*parsing(int argc, char *argv[], char *envp[])
{
	t_arg	*arg;

	arg = init_arg();
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		arg->here_doc = 1;
		arg->limitor = ft_strdup(argv[2]);
	}
	arg->path = get_path(envp);
	if (arg->path == 0)
		perror("Failed get path");
	arg->cmd_list = create_cmd_list(argc, argv, arg);
	arg->fds = malloc_fds(arg->cmd_count);
	if (arg->fds == 0)
		p_a_error(arg);
	arg->envp = envp;
	if (dup_file(argv, arg) == 0)
		p_a_error(arg);
	return (arg);
}

t_arg	*init_arg(void)
{
	t_arg	*arg;

	arg = 0;
	arg = ft_calloc(1, sizeof(t_arg));
	if (arg == 0)
		return (0);
	arg->cmd_list = 0;
	arg->cmd_count = 0;
	arg->fds = 0;
	arg->envp = 0;
	arg->infile = 0;
	arg->outfile = 0;
	arg->path = 0;
	arg->here_doc = 0;
	arg->limitor = 0;
	return (arg);
}

int	**malloc_fds(int cmd_count)
{
	int	**fds;
	int	i;

	fds = (int **)ft_calloc(cmd_count + 1, sizeof(int *));
	if (fds == 0)
		return (0);
	i = -1;
	while (++i < cmd_count)
	{
		fds[i] = (int *)ft_calloc(2, sizeof(int));
		if (fds[i] == 0)
		{
			free_fds(fds);
			return (0);
		}
	}
	return (fds);
}

int	dup_file(char *argv[], t_arg *arg)
{
	int	 i;

	i = -1;
	arg->infile = ft_strdup(argv[1]);
	if (arg->infile == 0)
		return (0);
	while (argv[++i] != 0)
	{
		if (argv[i + 1] == 0)
		{
			arg->outfile = ft_strdup(argv[i]);
			if (arg-> outfile == 0)
				return (0);
			return (1);
		}
	}
	return (0);
}
