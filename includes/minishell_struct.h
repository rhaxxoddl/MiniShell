/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:35:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/10 08:55:36 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

enum e_redir_type{
	HERE_DOC = 1,
	REDIR_IN = 2,
	REDIR_OUT = 3,
	REDIR_APP = 4
};

typedef struct s_redir{
	int				redir_type;
	char			*filename;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd{
	int				cmd_idx;
	char			**cmd_p;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_cmd_arg{
	t_cmd	*cmd_head;
	char	**path;
	int		cmd_count;
	int		**fds;
}				t_cmd_arg;

typedef struct s_arg{
	t_cmd_arg	*cmd_arg;
	int			status;
	char		**envp;
}				t_arg;

#endif
