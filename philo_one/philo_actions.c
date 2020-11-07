/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:33:50 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 17:48:32 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		takes_fork(int num, t_philo *philo)
{
	//ft_sleep(timestamp() + 1, philo);
	pthread_mutex_lock(&philo->right_fork->mutex_fork);
	if (!(write_message(num, philo, " has taken a fork.\n")))
		return (0);
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	if (!(write_message(num, philo, " has taken a fork.\n")))
		return (0);
//	ft_sleep(timestamp() + 1, philo);
	return (1);
}

int		eats(int num, t_philo *philo)
{
	philo->is_eating = 1;
	philo->death = timestamp() + philo->data->time_to_die;
	if (!(write_message(num, philo, " is eating.\n")))
		return (0);
	//if (philo->data->time_to_die)
	ft_sleep(timestamp() + philo->data->time_to_eat, philo);
	philo->count_meals++;
//	philo->last_meal = timestamp();
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
	
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	if (!(write_message(num, philo, " puts down his forks.\n")))
		return (0);
	ft_sleep(timestamp() + 1, philo);
	return (1);
}
