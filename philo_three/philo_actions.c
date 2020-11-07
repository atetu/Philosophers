/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:33:50 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 16:51:43 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	takes_fork(int num, t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	write_message(num, philo, " has taken a fork.\n");
	sem_wait(philo->data->sem_forks);
	write_message(num, philo, " has taken a fork.\n");
}

void	eats(int num, t_philo *philo)
{
	philo->is_eating = 1;
	philo->death = timestamp() + philo->data->time_to_die;
	write_message(num, philo, " is eating.\n");
	philo->count_meals++;
	ft_sleep(timestamp() + philo->data->time_to_eat, philo);
	philo->is_eating = 0;
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
