/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:33:50 by alicetetu         #+#    #+#             */
/*   Updated: 2020/10/13 14:49:12 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	takes_fork(int num, t_philo *philo)
{
	if (!philo->data->nb_deaths)
	{
		sem_wait(philo->data->sem_forks);
		write_message(num, philo, " has taken a fork.\n");
	}
	if (!philo->data->nb_deaths)
	{
		sem_wait(philo->data->sem_forks);
		write_message(num, philo, " has taken a fork.\n");
	}
	ft_sleep(timestamp() + 1, philo);
}

void	eats(int num, t_philo *philo)
{
	philo->is_eating = 1;
	write_message(num, philo, " is eating.\n");
	philo->count_meals++;
	ft_sleep(timestamp() + philo->data->time_to_eat, philo);
	philo->death = timestamp() + philo->data->time_to_die;
	philo->is_eating = 0;
	ft_sleep(timestamp() + 1, philo);
}

void	sleeps(int num, t_philo *philo)
{
	write_message(num, philo, " is sleeping.\n");
	ft_sleep(timestamp() + philo->data->time_to_sleep, philo);
}

void	puts_down_forks(int num, t_philo *philo)
{
	if (!philo->data->nb_deaths)
		sem_post(philo->data->sem_forks);
	if (!philo->data->nb_deaths)
	{
		sem_post(philo->data->sem_forks);
		write_message(num, philo, " puts down his forks.\n");
	}
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
