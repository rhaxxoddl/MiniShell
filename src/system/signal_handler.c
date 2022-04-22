/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:10:28 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/07 21:01:14 by                  ###   ########.fr       */
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
void    handle_sigterm(pid_t pid);


void	sig_init(void)
{
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, (void *)sig_handler);
	signal(SIGTERM, (void *)sig_handler);
}

void	sig_handler(int signo)
{
	pid_t	pid;
//	int		status;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signo == SIGINT)
		handle_sigint(pid);
	else if (signo == SIGQUIT)
		handle_sigquit(pid);
	else if (signo == SIGTERM)
		handle_sigterm(pid);
}

void    handle_sigterm(pid_t pid)
{
	if (pid == -1)
		return;
	rl_on_new_line();
	rl_redisplay();
//	rl_replace_line();
}

void    handle_sigint(pid_t pid)
{
	if (pid == -1)
		return;
	rl_on_new_line();
	rl_redisplay();
	write(2, " \n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void    handle_sigquit(pid_t pid)
{
	printf("sigquit\n");
	write(2, "\b\b\b\b", 4);
	if (pid == -1)
		return;
	rl_on_new_line();
	rl_redisplay();
}
