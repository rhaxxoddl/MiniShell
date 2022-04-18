/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:38:46 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/18 21:39:06 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "pipe_struct.h"
# include <stdio.h>
# include <readline/readline.h>

// parsing_util.c
char	*s_quotes(char **line);
char	*d_quotes(char **line, t_env *env_head);
int		valid_dol(char *line);

// parsing.c
char	*trans_env(char **line, t_env *env_head);
char	*app_str(char *dest, char *src);
t_cmd	*add_cmd(char *cmd_line);
t_cmd	*parsing_split(char **line, t_env *env_head);
int		pro_d_quotes(char **temp, char **line, t_env *env_head, int *i);
int		pro_s_quotes(char **temp, char **line, int *i);
int		pro_env(char **temp, char **line, t_env *env_head, int *i);
#endif