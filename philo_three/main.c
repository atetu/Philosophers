/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:28:43 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 16:38:57 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void __attribute__((destructor))
	on_stop(void)
{
	while (1)
		;
}

static void	kill_process(t_data *data, t_philo *philo)
{
	int i;
	pid_t pid;

	i = 0;
	while (i < data->nb_philo)
	{
		if ((pid = philo[i].process))
			kill(philo[i].process, SIGKILL);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	*array_wait_pid;

	data = NULL;
	philo = NULL;
	if (argc < 5 || argc > 6)
		return (error("Wrong number of arguments.\n"));
	if (!(data = (init_data(argc, argv))))
		return (0);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("dead");
	if (!(philo = init_philo(data)))
		return (1);
	init_process(philo, data->nb_philo);
	
	if (!(array_wait_pid = thread_wait_pid(philo)))
		return (exit_philo_data(philo, 0));
	if (!(thread_wait_death_or_meals(data, philo)))
		return (exit_philo_data_array(philo, array_wait_pid, 0));
	kill_process(data, philo);
	return (exit_philo_data_array(philo, array_wait_pid, 0));
}
