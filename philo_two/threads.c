/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:26:53 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/04 16:48:35 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_threads_meals(t_philo *philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i].thread_meal, NULL, &routine_meals,
					(void*)&philo[i]))
		{
			exit_philo(philo, 1);
			return (error("Problem during thread creation.\n"));
		}
		i++;
	}
	return (0);
}

int		init_threads(t_philo *philo, int nb_philo)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i].thread_philo, NULL, &routine_philo,
			(void*)&philo[i]))
		{
			exit_data(philo[i].data, "Problem during thread creation.\n");
			clear_philo(philo);
			return (1);
		}
		if (pthread_create(&philo[i].control_death, NULL,
			&philo_dies, (void*)&philo[i]))
		{
			exit_data(philo[i].data, "Problem during thread creation.\n");
			clear_philo(philo);
			return (1);
		}
		i++;
		ft_sleep(timestamp() + 2, philo);
	}
	return (0);
}
