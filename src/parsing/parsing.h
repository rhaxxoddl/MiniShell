/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:38:46 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/18 09:22:09 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "pipe_struct.h"
# include <stdio.h>
# include <readline/readline.h>

// quotes.c
char	*pro_quotes(char *line);

/*
[check_quotes()]
Check the quotes are correct.
If quotes is correct return 1.
else return 0.
*/
int		check_quotes(char *line);
char	*s_quotes(char **line);
char	*d_quotes(char **line, char **envp);

// parsing.c
char	*pro_env(char **line, char **envp);
char	*app_str(char *dest, char *src);
t_cmd	*add_cmd(char *cmd_line);
t_cmd	*parsing_split(char **line, char **envp);
#endif