/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:38:46 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/03 10:13:59 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "pipe_struct.h"
# include "../system/run_cmd.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>

// parsing_util.c
void	print_arg(t_cmd_arg *arg);
void	skip_space(char **line, int *i);
char	*app_str(char *dest, char *src);
char	**add_col(char **cmd, char **add);
void	pro_before_str(char **temp, char **line, int *i);

// parsing.c
t_arg		*init_arg(char **envp);
t_cmd_arg	*parsing(char **envp, char *line);
void		add_cmd(t_cmd_arg *cmd_arg, t_cmd **temp_cmd, char **envp, char **line);
t_cmd		*parsing_cmd(char **envp, char **line);

// init.c
t_arg	*init_arg(char **envp);
char	*get_env(char **envp, char *key);

// parsing_redir.c
void	parsing_redir(char **envp, t_cmd *cmd, char **line, int *i);
int		get_redir_type(char *c);
t_redir	*pro_redir(char **envp, char **line, int redir_type, int *i);
void	pro_switch(char **line, int *i, char **temp, char **envp);

// parsing_quotes.c
void	pro_d_quotes(char **envp, char **temp, char **line, int *i);
void	pro_s_quotes(char **temp, char **line, int *i);
char	*s_quotes(char **line);
char	*d_quotes(char **envp, char **line);

// parsing_env.c
int		valid_dol(char *line);
void	pro_env(char **envp, char **temp, char **line, int *i);
char	*trans_env(char **envp, char **line);

// free.c
void	free_str_arr(char **path);
void	free_reidr(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_fds(int **fds);
void	free_cmd_arg(t_cmd_arg *cmd_arg);

#endif