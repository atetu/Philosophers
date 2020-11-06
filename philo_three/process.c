/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:26:53 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 15:36:22 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			init_threads_meals(t_philo *philo)
{
	if (pthread_create(&philo->thread_meal, NULL, &routine_meals,
		(void*)philo))
	{
		return (error("Problem during thread creation.\n"));
	}
	return (0);
}

void		init_process(t_philo *philo, int nb_philo)
{
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		if ((philo[i].process = fork()) == 0)
			routine_philo(&philo[i]);
		i++;
		usleep(500);
	}
	return;
}
