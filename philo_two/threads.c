/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <atetu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:26:53 by alicetetu         #+#    #+#             */
/*   Updated: 2020/06/05 17:44:38 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_threads_meals(t_philo **philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i]->thread_meal, NULL, routine_meals,
					(void*)philo[i]))
		{
			exit_philo(philo, 1);
			return (error("Problem during thread creation.\n"));
		}
		if (pthread_detach(philo[i]->thread_meal))
		{
			exit_philo(philo, 1);
			return (error("Problem during thread detachment.\n"));
		}
		i++;
	}
	if (pthread_create(&philo[0]->data->thread_total_meals, NULL,
				routine_total_meals, (void*)philo[0]))
	{
		exit_philo(philo, 1);
		return (error("Problem during thread creation.\n"));
	}
	return (0);
}

int		init_threads(t_philo **philo, int nb_philo)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i]->thread_philo, NULL, routine_philo,
					(void*)philo[i]))
		{
//			exit_philo(philo, 1);
			return (error("Problem during thread creation.\n"));
		}
		if (pthread_detach(philo[i]->thread_philo))
		{
//			exit_philo(philo, 1);
			return (error("Problem during thread detachment.\n"));
		}
		i++;
		usleep(100);
	}
	return (0);
}
