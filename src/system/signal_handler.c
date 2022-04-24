/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:10:28 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/24 14:33:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

void	sig_handler(int signo);
void    handle_sigint(pid_t pid);
void    handle_sigquit(pid_t pid);


void	sig_init(void)
{
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, (void *)sig_handler);
}

void	sig_handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signo == SIGINT)
		handle_sigint(pid);
	else if (signo == SIGQUIT)
		handle_sigquit(pid);
}

void    handle_sigint(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

void    handle_sigquit(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
	else
		write(1, "\b\bQuit: 3\n", 10);
}
