/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:11:44 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/05 17:31:33 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_pwd(char *argv[])
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		printf("[pwd] Error occur with errno: %s\n", strerror(errno));
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}