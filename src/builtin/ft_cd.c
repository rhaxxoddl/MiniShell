/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:41:36 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/25 20:35:44 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <limits.h>

int	ft_pwd()
{
	char	*buf;

	buf = (char *)ft_calloc(PATH_MAX, sizeof(char));
	if (buf == 0)
		return (0);
	buf =  *getcwd(buf, PATH_MAX);
	if (buf == 0)
	{
		free(buf);
		buf = 0;
		return (0);
	}
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	free(buf);
	return (1);
}

int	ft_cd(char *path)
{
	char	**split;

	split = ft_split(path, '/');
}

char	update_path(char *path)
{
	
}
