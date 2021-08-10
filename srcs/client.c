/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 23:18:50 by mballet           #+#    #+#             */
/*   Updated: 2021/08/10 13:41:23 by mballet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_sigusr(int sig)
{
	(void)sig;
}

int	client(char *pid_srv, char *str)
{
	int					pid_s;
	long int			size_str;
	long int			i;
	int					j;
	struct sigaction	usr;

	pid_s = ft_atoi(pid_srv);
	if (!pid_s)
		return (0);
	size_str = ft_strlen(str);
	usr.sa_handler = &handle_sigusr;
	if ((sigaction(SIGUSR1, &usr, NULL)) < 0)
		return (0);
	i = -1;
	while (++i < size_str + 1)
	{
		j = 8;
		while (--j >= 0)
		{
			if (!((str[i] >> j) & 1))
				kill(pid_s, SIGUSR1);
			else
				kill(pid_s, SIGUSR2);
			usleep(1000);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (-1);
	if (!(client(argv[1], argv[2])))
		return (-1);
	return (0);
}
