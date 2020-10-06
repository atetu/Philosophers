/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <atetu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:44:11 by alicetetu         #+#    #+#             */
/*   Updated: 2020/06/04 18:44:15 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void				*routine_philo(void *philo)
{
	t_philo			*p;
	pthread_t		control_death;
	struct timeval	start;

	p = (t_philo*)philo;
	gettimeofday(&start, NULL);
	p->start = start.tv_sec * 1000000 + start.tv_usec;
	p->death = p->start + p->data->time_to_die;
	if (pthread_create(&control_death, NULL, philo_dies, philo)
			|| pthread_detach(control_death))
	{
		write_message(0, philo, "Problem during memory allocation.\n");
		pthread_mutex_unlock(&p->data->mutex_died);
		return ((void*)1);
	}
	while (p->dead == 0 && p->data->nb_deaths == 0)
	{
		takes_fork(p->num, p);
		eats(p->num, p);
		puts_down_forks(p->num, p);
		sleeps(p->num, p);
		write_message(p->num, p, " is thinking.\n");
	}
	return (NULL);
}

void				*routine_meals(void *philo)
{
	t_philo *p;

	p = philo;
	while (1)
	{
		if (p->count_meals >= p->data->nb_needed_meals)
		{
			p->data->eaten_meals++;
			return ((void*)0);
		}
	}
	return (NULL);
}

void				*routine_total_meals(void *philo)
{
	t_philo *p;

	p = philo;
	while (1)
	{
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
	timestamp = time.tv_sec * 1000000 + time.tv_usec;
	return (timestamp);
}
