/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:44:11 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 17:11:01 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_dies(void *philo)
{
	t_philo				*p;
	unsigned long long	t;

	p = philo;
	while (1)
	{
		t = timestamp();
		if (p->death <= t && !p->is_eating)
		{
			p->data->end = 1;
			write_message(p->num, p, " dies.\n");
			sem_post(p->data->sem_dead);
			return ((void *)1);
		}
		t = 0;
	}
	return ((void *)0);
}

static void	*philo_actions(void *p)
{
	t_philo				*philo;

	philo = p;
	while (philo && philo->data->nb_deaths == 0)
	{
		takes_fork(philo->num, philo);
		eats(philo->num, philo);
		puts_down_forks(philo->num, philo);
		sleeps(philo->num, philo);
		write_message(philo->num, philo, " is thinking.\n");
		ft_sleep(timestamp() + 1, philo);
	}
	return (NULL);
}

void		*routine_philo(t_philo *philo)
{
	philo->start = philo->data->start;
	if (pthread_create(&philo->thread_actions, NULL, &philo_actions,
		(void*)philo))
	{
		write_message(0, philo, "Problem during thread creation.\n");
		return (NULL);
	}
	if (pthread_create(&philo->control_death, NULL, &philo_dies,
		(void*)philo))
	{
		write_message(0, philo, "Problem during thread creation.\n");
		return (NULL);
	}
	if (philo->data->nb_needed_meals != -1)
	{
		if (init_threads_meals(philo))
			return (NULL);
	}
	sem_wait(philo->data->sem_dead);
	return (NULL);
}

void		*routine_meals(void *philo)
{
	t_philo *p;

	p = philo;
	while (1)
	{
		if (p->count_meals >= p->data->nb_needed_meals && p->global_meals == 0)
		{
			p->global_meals = 1;
			sem_post(p->data->sem_meals);
			break ;
		}
	}
	return (NULL);
}
