/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/05/02 21:39:20 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtin.h"

int	find_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		++i;
	return (i);
}

static int	ft_strcmp_j(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	result;

	len1 = find_end(s1);
	len2 = find_end(s2);
	if (len1 < len2)
	{
		result = ft_strncmp(s1, s2, len1);
		if (result == 0)
			return (-1);
		return (result);
	}
	else
	{
		result = ft_strncmp(s1, s2, len2);
		if (result == 0 && len1 > len2)
			return (1);
		return (result);
	}
}

static void	_print_envp(char *envp[], char *arr, int cur, int i)
{
	while (1)
	{
		cur = -1;
		i = -1;
		while (envp[++i])
		{
			if (envp[i][0] == '?' || arr[i])
				continue ;
			if (cur == -1)
				cur = i;
			else
			{
				if (ft_strcmp_j(envp[cur], envp[i]) > 0)
					cur = i;
			}
		}
		if (cur == -1)
			break ;
		ft_putstr_fd("declare -x ", 1);
		ft_putstrendl_fd(envp[cur], 1);
		arr[cur] = 1;
	}
}

void	print_envp(char *envp[])
{
	int		len;
	char	*arr;

	len = 0;
	while (envp[len])
		++len;
	arr = ft_calloc(len, sizeof(char));
	if (!arr)
		exit(EXIT_FAILURE);
	_print_envp(envp, arr, 0, 0);
	free(arr);
}
