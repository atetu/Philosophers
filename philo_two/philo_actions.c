/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <atetu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:33:50 by alicetetu         #+#    #+#             */
/*   Updated: 2020/06/05 20:23:46 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	takes_fork(int num, t_philo *philo)
{

/*	if (philo->right_fork->num > philo->left_fork->num)
	{
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		pthread_mutex_lock(&philo->mutex_alive);
		write_message(num, philo, " has taken a fork.\n");
		pthread_mutex_unlock(&philo->mutex_alive);
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		pthread_mutex_lock(&philo->mutex_alive);
		write_message(num, philo, " has taken a fork.\n");
		pthread_mutex_unlock(&philo->mutex_alive);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		pthread_mutex_lock(&philo->mutex_alive);
		write_message(num, philo, " has taken a fork.\n");
		pthread_mutex_unlock(&philo->mutex_alive);
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		pthread_mutex_lock(&philo->mutex_alive);
		write_message(num, philo, " has taken a fork.\n");
		pthread_mutex_unlock(&philo->mutex_alive);
	}*/
}

void	eats(int num, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_alive);
	philo->is_eating = 1;
	write_message(num, philo, " is eating.\n");
	usleep(philo->data->time_to_eat);
	philo->count_meals++;
	philo->last_meal = timestamp();
	philo->death = timestamp() + philo->data->time_to_die;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex_alive);
}

void	sleeps(int num, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_alive);
	write_message(num, philo, " is sleeping.\n");
	pthread_mutex_unlock(&philo->mutex_alive);
	usleep(philo->data->time_to_sleep);
	pthread_mutex_unlock(&philo->mutex_alive);
}

void	puts_down_forks(int num, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_alive);
	write_message(num, philo, " puts down his forks.\n");
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	pthread_mutex_unlock(&philo->mutex_alive);
}

void	*philo_dies(void *philo)
{
	t_philo *p;

	p = philo;
	while (1)
	{
		pthread_mutex_lock(&p->mutex_alive);
		if (!(p->is_eating) && p->death <= timestamp())
		{
			write_message(p->num, p, " dies.\n");
			p->dead = 1;
			p->data->nb_deaths = 1;
			pthread_mutex_unlock(&p->data->mutex_died);
			return ((void *)1);
		}
		pthread_mutex_unlock(&p->mutex_alive);
	}
}
