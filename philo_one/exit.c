/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <atetu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:49:05 by alicetetu         #+#    #+#             */
/*   Updated: 2020/06/04 16:49:09 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		exit_philo(t_philo **philo, int n)
{
	int nb;

	if (philo && philo[0])
	{
		nb = philo[0]->data->nb_philo;
		clear_forks(philo[0]->data->forks, nb);
		clear_data(philo[0]->data);
		clear_philo(philo, nb);
	}
	return (n);
}

void	*exit_data(t_data *data, char *str)
{
	clear_data(data);
	return (error_data(str));
}

void	clear_forks(t_fork **forks, int nb)
{
	int i;

	i = 0;
	if (forks)
	{
		while (i < nb)
		{
			if (forks[i])
			{
				pthread_mutex_destroy(&forks[i]->mutex_fork);
				free(forks[i]);
				forks[i] = NULL;
			}
			i++;
		}
		free(forks);
		forks = NULL;
	}
}

void	clear_data(t_data *data)
{
	if (data)
	{
		pthread_mutex_destroy(&data->mutex_write);
		pthread_mutex_destroy(&data->mutex_died);
		free(data);
		data = NULL;
	}
}

void	clear_philo(t_philo **philo, int nb)
{
	int i;

	i = 0;
	if (philo)
	{
		i = 0;
		while (i < nb)
		{
			if (philo[i])
			{
				pthread_mutex_destroy(&philo[i]->mutex_alive);
				free(philo[i]);
				philo[i] = NULL;
			}
			i++;
		}
		free(philo);
		philo = NULL;
	}
}
