/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:11:44 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/28 17:55:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
///////////////////
void	ft_putstrendl_fd(char *s, int fd);

int	ft_pwd(char *argv[])
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstrendl_fd(strerror(errno), 2);
		return (0);
	}
	ft_putstr_fd(pwd, 1);
	free(pwd);
	return (1);
}