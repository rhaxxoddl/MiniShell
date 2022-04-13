/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:44:48 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/13 20:05:47 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str = ft_strdup("abcd$P'ATH pad$'PATH");

	printf("str : %s\n", str);
	parsing_split(&str, envp);
	// while (1)
	// {
	// }
	return (0);
}