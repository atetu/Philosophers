/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:44:11 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 13:09:02 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void				*routine_philo(void *philo)
{
	t_philo			*p;
	pthread_t		control_death;
	pthread_t		thread_philo_actions;

	p = (t_philo*)philo;
	p->start = p->data->start;
	if (pthread_create(&control_death, NULL, &philo_dies, philo)
		|| pthread_create(&thread_philo_actions, NULL, &philo_action, philo))
	{
		write_message(0, philo, "Problem during memory allocation.\n");
		pthread_mutex_unlock(&p->data->mutex_died);
		return ((void*)1);
	}
	while (p->data->nb_deaths == 0)
	{
	}
	return (NULL);
}

void				*routine_meals(void *philo)
{
	t_philo *p;

	p = philo;
	while (1)
	{
		if (p->data->nb_deaths == 1)
			break ;
		if (p->count_meals >= p->data->nb_needed_meals && p->global_meals == 0
			&& p->data->nb_deaths == 0)
		{
			p->data->eaten_meals++;
			p->global_meals = 1;
			if (p->data->eaten_meals >= p->data->nb_philo)
			{
				p->data->end = 1;
				write_message(p->num, p, "END OF SIMULATION.\n");
				pthread_mutex_unlock(&p->data->mutex_died);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

void				*routine_total_meals(void *philo)
{
	t_philo *p;

	p = philo;
	while (1)
	{
		if (p->data->nb_deaths == 1)
			break ;
		if (p->data->eaten_meals >= p->data->nb_philo)
		{
			pthread_mutex_unlock(&p->data->mutex_died);
			return (0);
		}
	}
	return (NULL);
}

unsigned long long	timestamp(void)
{
	struct timeval		time;
	unsigned long long	timestamp;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp);
}

void				ft_sleep(unsigned long long end, t_philo *philo)
{
	while (timestamp() < end && philo->data->nb_deaths == 0)
		usleep(500);
}
