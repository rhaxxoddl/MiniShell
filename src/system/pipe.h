/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:51:05 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/22 20:46:30 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "libft.h"
# include "pipe_struct.h"
# include <stdio.h>

# define R 0
# define W 1

/*
To do list
1. create free_arg()
2. create here_doc()
3. If argv[1] is "here_doc" create_cmd_list starts with argv[3]
*/

// cmd.c
t_cmd_list	*create_cmd_list(int argc, char *argv[], t_arg *arg);
t_cmd_list	*add_cmd_list(char *cmd_str, char *path[], int cmd_idx);
char		*cmd_connect_path(char *cmd, char **path);
// error.c
void		p_a_error(t_arg *arg);
// free_array.c
void		free_str_arr(char **str_arr);
void		free_path(char **path);
void		free_fds(int **fds);
// free_struct.c
void		free_arg(t_arg *arg);
void		clear_cmd_list(t_cmd_list *head);
void		free_cmd_list(t_cmd_list *dest);
// ft_split.c
char		**ft_split_p(char const *s, char c);
//parsing.c
t_arg		*parsing(int argc, char *argv[], char *envp[]);
t_arg		*init_arg(void);
int			**malloc_fds(int cmd_count);
int			dup_file(char *argv[], t_arg *arg);
// path.c
char		**get_path(char *envp[]);
char		*add_pwd(char *envp[]);
int			add_slash(char **path);
// pipe.c
int			ft_pipe(t_arg *arg, t_cmd_list *cmd_list);
void		connect_pipe(int cmd_idx, t_arg *arg);
// redirection.c
int			redir_in(const char *filename);
int			redir_out(const char *filename);
int			redir_app(const char *filename);
#endif
