/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:15:38 by atetu             #+#    #+#             */
/*   Updated: 2020/11/07 16:52:05 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t	*thread_wait_pid(t_philo *philo)
{
	pthread_t	*thread_wait_pid;
	int			i;
	int			nb_process;

	i = 0;
	nb_process = philo[0].data->nb_philo;
	if (!(thread_wait_pid = malloc(sizeof(pthread_t) * nb_process)))
		return (0);
	while (i < nb_process)
	{
		if (pthread_create(&thread_wait_pid[i], NULL, &monitor_each_pid,
			(void*)&philo[i]))
		{
			free(thread_wait_pid);
			return (0);
		}
		i++;
	}
	return (thread_wait_pid);
}

int			thread_wait_death_or_meals(t_data *data, t_philo *philo)
{
	pthread_t	thread_global_meals;
	pthread_t	thread_global_death;

	if (data->nb_needed_meals != -1)
	{
		if ((pthread_create(&thread_global_meals, NULL,
			&monitor_global_meals, (void*)philo))
			|| (pthread_create(&thread_global_death, NULL,
			&monitor_global_death, (void*)data)))
		{
			write_message(0, &philo[0], "Problem during thread creation.\n");
			return (0);
		}
		while (1)
			if (data->end == 1)
				return (1);
	}
	else
	{
		while (1)
			if (data->end == 1)
				return (1);
	}
	return (1);
}
