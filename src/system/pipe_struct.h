/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:35:32 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/24 21:05:16 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_STRUCT_H
# define PIPE_STRUCT_H
# include "pipe.h"

// typedef struct s_cmd_list{
// 	char				*cmd;
// 	char				**cmd_with_option;
// 	char				*cmd_path;
// 	int					cmd_idx;
// 	struct s_cmd_list	*next;
// }				t_cmd;

// typedef struct s_arg{
// 	t_cmd_list	*cmd_list;
// 	int			cmd_count;
// 	int			**fds;
// 	char		**envp;
// 	char		*infile;
// 	char		*outfile;
// 	char		**path;
// 	int			here_doc;
// 	char		*limitor;
// 	int			status;
// }				t_arg;

enum redir_type{
	HERE_DOC = 1,
	REDIR_IN = 2,
	REDIR_OUT = 3,
	REDIR_APP = 4
};

typedef struct s_redir{
	int		redir_type; // enum으로 here_doc = 0, redir_in = 1, redir_out = 2, redir_app = 3으로 지정
	char	*filename; // redirection에 들어갈 filename
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd{
	char	**cmd; // [0]은 적절한 path가 연결된 cmd, [1]부터 cmd에 들어갈 인자
	t_redir	*redir;
}				t_cmd;

typedef struct s_arg{
	t_cmd	*c_t; // 명령어 구조체 (파이프를 구분자로 끊어서 한 명령어 구조체에 넣는다)
	int		cmd_count; // 명령어 구조체 수
	int		cmd_idx; // 명령어 인덱스
	int		**fds;
	int		status; // 마지막 exit code 저장
	char	**envp;
	int		std_out;
	int		std_in;
}				t_arg;

#endif
