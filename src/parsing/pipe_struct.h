/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:35:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/18 13:50:05 by sanjeon          ###   ########.fr       */
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
	char			**cmd;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_arg{
	t_cmd	*c_t;
	int		cmd_count;
	int		cmd_idx;
	int		**fds;
	int		status;
	char	**envp;
	int		std_out;
	int		std_in;
}				t_arg;

#endif
