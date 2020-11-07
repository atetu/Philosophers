/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:49:05 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 16:49:46 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		exit_philo_data(t_philo *philo, int n)
{
	if (philo)
	{
		clear_data(philo[0].data);
		clear_philo(philo);
	}
	return (n);
}

int		exit_philo_data_array(t_philo *philo, pthread_t *array_wait_pid, int n)
{
	usleep(1000);
	if (philo)
	{
		clear_data(philo[0].data);
		clear_philo(philo);
		clear_array_wait_pid(array_wait_pid);
	}
	return (n);
}

void	*exit_data(t_data *data, char *str)
{
	clear_data(data);
	return (error_data(str));
}
