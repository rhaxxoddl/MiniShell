/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:44:48 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/22 17:27:33 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	t_arg	*arg;
	char	*str = ft_strdup("\'abcd$PATH\' pad$PATH > abcd   asf | <hihi ls -al");

	env = get_env(envp);
	arg = parsing(str, env);
	print_arg(arg);
	// printf("str : %s\n", str);
	// parsing_split(&str, env);
	return (0);
}