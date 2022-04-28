/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:11:03 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/28 21:23:29 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

// ft_export.c
void	ft_export(char *argv[], char *envp[]);

//ft_cd.c

// builtin_utils.c
void	ft_putstrendl_fd(char *s, int fd);
// ft_echo.c
int	ft_echo(char *argv[]);
// ft_env.c
void	ft_env(char *argv[], char *envp[]);
// ft_exit.c
void	ft_exit(char *argv[]);
// ft_export_print.c
void print_envp(char *envp[]);
// ft_pwd.c
int	ft_pwd(void);
// ft_unset.c
void	ft_unset(char *argv[], char *envp[]);
#endif