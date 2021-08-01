/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 23:19:02 by mballet           #+#    #+#             */
/*   Updated: 2021/08/02 00:08:53 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*fill_in_str(char *str, char c)
{
	size_t	size;

	size = 0;
	if (!str)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = c;
		str[1] = 0;
	}
	else
	{
		size = ft_strlen(str);
		str = ft_realloc(str, size + 1);
		if (!str)
			return (NULL);
		str[size] = c;
		str[size + 1] = 0;
	}
	return (str);
}

static void	signal_received(siginfo_t *siginfo, void *context)
{
	static int			pid_client = 0;

	if (siginfo->si_pid != 0)
		pid_client = siginfo->si_pid;
	kill(pid_client, SIGUSR1);
	(void)context;
}

static void	handle_sigusr(int sig, siginfo_t *siginfo, void *context)
{
	static unsigned int	val = 0;
	static int			i = 8;
	unsigned char		chaar;
	static char			*str = NULL;

	if (sig == SIGUSR2)
		val = val | (1 << (i - 1));
	if (--i == 0)
	{
		chaar = (char)val;
		val = 0;
		i = 8;
		str = fill_in_str(str, chaar);
		if (!str)
			write(1, "Error malloc\n", 13);
		if (!chaar)
		{
			ft_putstr_fd(str, 1);
			write(1, "\nRecieved !\n", 12);
			free(str);
			str = NULL;
		}
	}
	signal_received(siginfo, context);
}

int	main(void)
{
	int					pid;
	int					chaar;
	struct sigaction	usr;

	chaar = 0;
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	usr.sa_sigaction = &handle_sigusr;
	usr.sa_flags = SA_SIGINFO;
	if ((sigaction(SIGUSR1, &usr, NULL)) < 0)
		return (0);
	if ((sigaction(SIGUSR2, &usr, NULL)) < 0)
		return (0);
	while (1)
		pause();
	return (0);
}
