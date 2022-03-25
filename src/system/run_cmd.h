/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:51:05 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/25 17:02:59 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_CMD_H
# define RUN_CMD_H

# include "libft.h"
# include "pipe_struct.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# define R 0
# define W 1

// error.c
void		p_a_error(t_arg *arg);
// ft_split.c
char		**ft_split_p(char const *s, char c);
// main.c
//parsing.c
t_arg		*init_arg(void);
int			**malloc_fds(int cmd_count);
int			dup_file(char *argv[], t_arg *arg);
// path.c
char		**get_path(char *envp[]);
char		*add_pwd(char *envp[]);
int			add_slash(char **path);
// pipe.c
int			run_cmd(t_arg *arg, int i);
void		connect_pipe(int cmd_idx, t_arg *arg);
void		connect_redir(t_redir *redir, t_arg *arg);
int			sellect_redir(t_redir *redir);
// redirection.c
int			redir_in(const char *filename);
int			redir_out(const char *filename);
int			redir_app(const char *filename);
int			redir_here(const char *limitor);
// here_doc_util.c
int			until_comein_limitor(char **str, char **rl,
				const char *limitor, int fd);
int			free_return(char **str, char **rl, int status);
int			comein_limitor(int fd, char **str, char **rl);
char		*is_limitor(char *str, const char *limitor);
char		*add_str(char **str, char **rl);
#endif