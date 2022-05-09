/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:11:03 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/02 21:37:45 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"

// builtin_utils.c
void	ft_putstrendl_fd(char *s, int fd);

//ft_cd.c
int		ft_cd(char *argv[], char **envp[]);

// ft_echo.c
int		ft_echo(char *argv[]);

// ft_env.c
int		ft_env(char *argv[], char *envp[]);

// ft_exit.c
void	ft_exit(char *argv[]);

// ft_export.c
int		ft_export(char *argv[], char **envp[]);
void	update_env(char *str, char **envp[]);

// ft_export_print.c
int		find_end(char *str);
void	print_envp(char *envp[]);

// ft_pwd.c
int		ft_pwd(void);

// ft_unset.c
int		ft_unset(char *argv[], char **envp[]);

#endif
