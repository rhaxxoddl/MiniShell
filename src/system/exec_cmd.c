/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/27 15:10:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "builtin.h"
///////////
int		ft_echo(char *argv[]);
int		ft_cd(char *path);
int		ft_pwd(char *argv[]);
void	ft_export(char *argv[], char *envp[]);
void	ft_unset(char *argv[], char *envp[]);
void	ft_env(char *argv[], char *envp[]);
void	ft_exit(char *argv[]);
///////////

void exec_cmd(char *argv[], char *envp[])
{
	if (ft_strncmp("echo", argv[0], 4) == 0)
		ft_echo(argv);
	else if (ft_strncmp("cd", argv[0], 2) == 0)
		ft_cd(argv[1]); // not sure about hot to use
	else if (ft_strncmp("pwd", argv[0], 3) == 0)
		ft_pwd(argv);
	else if (ft_strncmp("export", argv[0], 6) == 0)
		ft_export(argv, envp);
	else if (ft_strncmp("unset", argv[0], 5) == 0)
		ft_unset(argv, envp);
	else if (ft_strncmp("env", argv[0], 3) == 0)
		ft_env(argv, envp);
	else if (ft_strncmp("exit", argv[0], 4) == 0)
		ft_exit(argv);
	else
	{
		/*
		 * sanjeon's code here
		 */
	}
}