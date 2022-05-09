/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/05/02 21:39:56 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "builtin.h"

static int	chdir_home(char *envp[])
{
	int		i;
	int		status;
	char	*path;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("HOME=", envp[i], 5) == 0)
			break ;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	status = chdir(path);
	if (path)
		free(path);
	if (status < 0)
		ft_putstrendl_fd("minishell: cd: HOME not set", 2);
	return (status);
}

static int	chdir_oldpwd(char *envp[])
{
	int		i;
	int		status;
	char	*path;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("OLDPWD=", envp[i], 7) == 0)
			break ;
	path = ft_substr(envp[i], 7, ft_strlen(envp[i]) - 7);
	status = chdir(path);
	if (path)
		free(path);
	if (status < 0)
		ft_putstrendl_fd("minishell: cd: OLDPWD not set", 2);
	return (status);
}

static int	chdir_path(char *path)
{
	int	status;

	status = chdir(path);
	if (status < 0)
		perror(NULL);
	return (status);
}

static int	update_pwd(char *oldpwd, char **envp[])
{
	char	*new_env;
	char	*pwd;

	new_env = ft_strjoin("OLDPWD=", oldpwd);
	if (!new_env)
		return (1);
	update_env(new_env, envp);
	free(new_env);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	new_env = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!new_env)
		return (1);
	update_env(new_env, envp);
	free(new_env);
	return (0);
}

int	ft_cd(char *argv[], char **envp[])
{
	int		i;
	int		status;
	char	*pwd;

	i = 0;
	while (argv[i])
		++i;
	if (i > 2)
	{
		ft_putstrendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	if (i == 1 || ft_strncmp("~\0", argv[1], 2) == 0)
		status = chdir_home(*envp);
	else if (ft_strncmp("-\0", argv[1], 2) == 0)
		status = chdir_oldpwd(*envp);
	else
		status = chdir_path(argv[1]);
	if (status == 0)
		status = update_pwd(pwd, envp);
	free(pwd);
	return (status);
}
