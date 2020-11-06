/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:30:54 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 15:31:48 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_each_pid(void *philo)
{
	int			status;
	t_philo		*p;
	
	p = philo;
	waitpid(p->process, &status, 0);
	p[0].data->end = 1;
	return (NULL);
}

void	*monitor_global_meals(void *philo)
{
	t_philo *p;
	int		i;
	
	i = 0;
	p = (t_philo *)philo;
	while (i < p->data->nb_philo)
	{
		sem_wait(p->data->sem_meals);
		i++;
	}
	p[0].data->end = 1;
	write_message(p[0].num, &p[0], "END OF SIMULATION.\n");
	return (NULL);
}

void	*process_wait_meals(void *philo)
{
	int i;
	t_philo *p;

	i = 0;
	p = philo;
	while (i < p->data->nb_philo)
	{
		sem_wait(p->data->sem_meals);
		i++;
	}
	p[0].data->end = 1;
	write_message(p[0].num, &p[0], "END OF SIMULATION.\n");
	return (NULL);
}

void	*monitor_global_death(void *data)
{
	t_data *d;

	d = data;
	sem_wait(d->sem_dead);
	d->end = 1;
	return (NULL);
}
