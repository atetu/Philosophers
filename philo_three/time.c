/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:30:24 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 15:32:45 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


unsigned long long	timestamp(void)
{
	struct timeval		time;
	unsigned long long	timestamp;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp);
}

void				ft_sleep(unsigned long long end, t_philo *philo)
{
	while (timestamp() < end && philo->data->nb_deaths == 0)
		usleep(500);
}
