/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:49:05 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 16:29:46 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int		exit_philo(t_philo *philo, int n)
{
	int	nb;

	if (philo)
	{
		nb = philo[0].data->nb_philo;
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
		clear_data(philo[0].data);
		clear_philo(philo);
	}
	return (n);
}

void	*exit_data(t_data *data, char *str)
{
	clear_data(data);
	return (error_data(str));
}

void	clear_data(t_data *data)
{
	if (data)
	{
		free(data);
		data = NULL;
	}
}

void	clear_philo(t_philo *philo)
{
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
}
