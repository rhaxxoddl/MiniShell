/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:10:28 by jinoh             #+#    #+#             */
/*   Updated: 2022/05/06 19:54:36 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>

void	sig_handler(int signo);
void	handle_sigint(pid_t pid);
void	handle_sigquit(pid_t pid);

void	sig_init(void)
{
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, (void *)sig_handler);
}

void	sig_init_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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

void	handle_sigint(pid_t pid)
{
	if (pid == -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "^C\n", 3);
}

void	handle_sigquit(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(1, "^\\Quit: 3\n", 10);
}
