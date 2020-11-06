/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:04:51 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 15:38:29 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

// void	clear_pid_philo(t_pid *pid_philo)
// {
// 	if (pid_philo)
// 	{
// 		free(pid_philo);
// 		pid_philo = NULL;
// 	}
// }

void	clear_array_wait_pid(pthread_t *array_wait_pid)
{
	if (array_wait_pid)
	{
		free(array_wait_pid);
		array_wait_pid = NULL;
	}
}
