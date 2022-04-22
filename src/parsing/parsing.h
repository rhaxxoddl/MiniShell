/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:38:46 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/22 17:06:00 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "pipe_struct.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>

// parsing_util.c
void	print_arg(t_arg *arg);
void	skip_space(char **line, int *i);
char	*app_str(char *dest, char *src);
char	**add_col(char **cmd, char *add);
int		pro_before_str(char **temp, char **line, int *i);

// parsing.c
t_arg	*parsing(char *line, t_env *env_head);
t_cmd	*parsing_cmd(char **line, t_env *env_head);
t_cmd	*add_cmd(char *cmd_line);

// init.c
t_env	*get_env(char **envp);
int		add_env(t_env **head, t_env **current, int *i);
char	*trans_env(char **line, t_env *env_head);

// parsing_redir.c
int		parsing_redir(t_cmd *cmd, char **line, t_env *env_head, int *i);
int		get_redir_type(char *c);
t_redir	*pro_redir(char **line, t_env *env_head, int redir_type, int *i);

// parsing_quotes.c
int		pro_d_quotes(char **temp, char **line, t_env *env_head, int *i);
int		pro_s_quotes(char **temp, char **line, int *i);
char	*s_quotes(char **line);
char	*d_quotes(char **line, t_env *env_head);

// parsing_env.c
int		valid_dol(char *line);
int		pro_env(char **temp, char **line, t_env *env_head, int *i);

// free.c
void	free_env(t_env *head);

#endif