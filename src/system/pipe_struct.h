/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:35:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/22 19:42:58 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_STRUCT_H
# define PIPE_STRUCT_H
# include "pipe.h"

typedef struct s_cmd_list{
	char				*cmd;
	char				**cmd_with_option;
	char				*cmd_path;
	int					cmd_idx;
	struct s_cmd_list	*next;
}				t_cmd_list;

typedef struct s_arg{
	t_cmd_list	*cmd_list;
	int			cmd_count;
	int			**fds;
	char		**envp;
	char		*infile;
	char		*outfile;
	char		**path;
	int			here_doc;
	char		*limitor;
	int			status;
}				t_arg;

#endif
