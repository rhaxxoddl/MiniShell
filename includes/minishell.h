/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:51:05 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/09 21:05:19 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"

# define R 0
# define W 1

// error.c-------------------------------------
void		ft_error(void);
void		ft_str_error(char *str);
void		cnf_error(char *cmd);

// run_cmd.c-----------------------------------
int			run_process(t_arg *arg, t_cmd_arg *cmd_arg);
void		run_cmd(t_arg *arg, t_cmd *cmd_head);
void		connect_pipe(int cmd_idx, t_cmd_arg *cmd_arg);
void		connect_redir(int cmd_idx, t_cmd_arg *cmd_arg, t_redir *redir);
void		exit_handle(t_arg *arg);

// redirection.c-----------------------------------
int			sellect_redir(t_redir *redir, int *out);
int			redir_in(const char *filename);
int			redir_out(const char *filename);
int			redir_app(const char *filename);
int			redir_here(const char *limitor);

// here_doc_util.c-----------------------------------
int			until_comein_limitor(const char *limitor, int fd);
int			comein_limitor(int fd, char **str, char **rl);
char		*is_limitor(char *rl, const char *limitor);
char		*here_app_str(char **str, char **rl);
char		*add_nl(char **str);

// connect_cmd.c-----------------------------------
char		**get_path(char **envp);
int			add_slash(char **path);
char		*cmd_connect_path(char *cmd, char **path);
int			**malloc_fds(int cmd_count);

// exec_cmd.c-----------------------------------
int			chk_builtin(char *argv[]);
void		update_status(char **envp[], int status);
void		exec_cmd(char *argv[], char **envp[], char **path);
int			exec_cmd_one(t_cmd_arg *cmd_arg, char *argv[], char **envp[]);
// signal_handler.c-----------------------------------
void		sig_init(void);
void		sig_init_child(void);
#endif
