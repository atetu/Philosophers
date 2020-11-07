/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:33:50 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 17:26:03 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		takes_fork(int num, t_philo *philo)
{
	ft_sleep(timestamp() + 1, philo);
	sem_wait(philo->data->sem_forks);
	if (!(write_message(num, philo, " has taken a fork.\n")))
		return (0);
	sem_wait(philo->data->sem_forks);
	if (!(write_message(num, philo, " has taken a fork.\n")))
		return (0);
	//ft_sleep(timestamp() + 1, philo);
	return (1);
}

int		eats(int num, t_philo *philo)
{
	philo->is_eating = 1;
	philo->death = timestamp() + philo->data->time_to_die;
	if (!(write_message(num, philo, " is eating.\n")))
		return (0);
	philo->count_meals++;
	ft_sleep(timestamp() + philo->data->time_to_eat, philo);
	philo->death = timestamp() + philo->data->time_to_die;
	philo->is_eating = 0;
//	ft_sleep(timestamp() + 1, philo);
	return (1);
}

int		sleeps(int num, t_philo *philo)
{
	if (!(write_message(num, philo, " is sleeping.\n")))
		return (0);
	ft_sleep(timestamp() + philo->data->time_to_sleep, philo);
	return (1);
}

int		puts_down_forks(int num, t_philo *philo)
{
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
	if (!(write_message(num, philo, " puts down his forks.\n")))
		return (0);
	return (1);
}

void	*philo_dies(void *philo)
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
			return ((void *)1);
		}
		t = 0;
	}
	return ((void *)0);
}
