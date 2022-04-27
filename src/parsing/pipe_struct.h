/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:35:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/27 19:21:10 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_STRUCT_H
# define PIPE_STRUCT_H

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
	char			**cmd_param;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd_arg{
	t_cmd	*cmd_head;
	char	**path;
	int		cmd_count;
	int		**fds;
}				t_cmd_arg;

typedef struct s_arg{
	t_cmd_arg	*cmd_arg;
	int			status;
	t_env		*env;
	char		**envp;
}				t_arg;

#endif
