/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/05/09 21:04:48 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	chk_builtin(char *argv[])
{
	if (argv[0] == 0)
		return (0);
	if (ft_strncmp("cd\0", argv[0], 3) == 0)
		return (1);
	else if (ft_strncmp("exit\0", argv[0], 5) == 0)
		return (1);
	else if (ft_strncmp("export\0", argv[0], 7) == 0)
		return (1);
	else if (ft_strncmp("unset\0", argv[0], 6) == 0)
		return (1);
	return (0);
}

void	update_status(char **envp[], int status)
{
	char	*exit_status;
	char	*status_char;

	status_char = ft_itoa(status);
	if (!status_char)
		exit(EXIT_FAILURE);
	exit_status = ft_strjoin("?=", status_char);
	if (!exit_status)
	{
		free(status_char);
		exit(EXIT_FAILURE);
	}
	update_env(exit_status, envp);
	free(status_char);
	free(exit_status);
}

int	exec_cmd_one(t_cmd_arg *cmd_arg, char *argv[], char **envp[])
{
	int	status;

	status = 0;
	if (ft_strncmp("cd\0", argv[0], 3) == 0)
		status = ft_cd(argv, envp);
	else if (ft_strncmp("export\0", argv[0], 7) == 0)
		status = ft_export(argv, envp);
	else if (ft_strncmp("unset\0", argv[0], 6) == 0)
		status = ft_unset(argv, envp);
	else if (ft_strncmp("exit\0", argv[0], 5) == 0)
		ft_exit(argv);
	update_status(envp, status);
	free_cmd_arg(cmd_arg);
	return (0);
}

void	exec_cmd(char *argv[], char **envp[], char **path)
{
	int	status;

	status = 0;
	if (ft_strncmp("echo\0", argv[0], 5) == 0)
		status = ft_echo(argv);
	else if (ft_strncmp("cd\0", argv[0], 3) == 0)
		status = ft_cd(argv, envp);
	else if (ft_strncmp("pwd\0", argv[0], 4) == 0)
		status = ft_pwd();
	else if (ft_strncmp("export\0", argv[0], 7) == 0)
		status = ft_export(argv, envp);
	else if (ft_strncmp("unset\0", argv[0], 6) == 0)
		status = ft_unset(argv, envp);
	else if (ft_strncmp("env\0", argv[0], 4) == 0)
		status = ft_env(argv, *envp);
	else if (ft_strncmp("exit\0", argv[0], 5) == 0)
		ft_exit(argv);
	else
	{
		argv[0] = cmd_connect_path(argv[0], path);
		execve(argv[0], argv, *envp);
	}
	exit(status);
}
