/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:44:48 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/18 17:15:35 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str = ft_strdup("\'abcd$PATH\' pad$PATH");

	if (ft_isalpha('\"') || ft_isalnum('\"'))
		printf("qoutes\n");
	printf("str : %s\n", str);
	parsing_split(&str, envp);
	// while (1)
	// {
	// }
	return (0);
}