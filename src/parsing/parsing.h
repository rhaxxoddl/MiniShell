/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:38:46 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/27 19:22:35 by sanjeon          ###   ########.fr       */
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
char	**add_col(char **cmd, char *add);
int		pro_before_str(char **temp, char **line, int *i);

// parsing.c
t_arg		*init_arg(char **envp);
t_cmd_arg	*parsing(t_env *env_head, char *line, char **envp);
t_cmd		*parsing_cmd(t_env *env_head, char **line);
t_cmd		*add_cmd(char *cmd_line);
// init.c
t_arg	*init_arg(char **envp);
t_env	*init_env(char **envp);
int		add_env(t_env **head, t_env **current, int *i);
char	*get_env(t_env *env_head, char *key);

// parsing_redir.c
int		parsing_redir(t_env *env_head, t_cmd *cmd, char **line, int *i);
int		get_redir_type(char *c);
t_redir	*pro_redir(t_env *env_head, char **line, int redir_type, int *i);

// parsing_quotes.c
int		pro_d_quotes(t_env *env_head, char **temp, char **line, int *i);
int		pro_s_quotes(char **temp, char **line, int *i);
char	*s_quotes(char **line);
char	*d_quotes(t_env *env_head, char **line);

// parsing_env.c
int		valid_dol(char *line);
int		pro_env(t_env *env_head, char **temp, char **line, int *i);
char	*trans_env(t_env *env_head, char **line);

// free.c
void	free_env(t_env *head);
void	free_path(char **path);

#endif