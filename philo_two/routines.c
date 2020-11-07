/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:44:11 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 17:27:56 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void				*routine_philo(void *philo)
{
	t_philo			*p;

	p = (t_philo*)philo;
	p->start = p->data->start;
	while (p && p->data->nb_deaths == 0)
	{
		takes_fork(p->num, p);
		eats(p->num, p);
		puts_down_forks(p->num, p);
		sleeps(p->num, p);
		write_message(p->num, p, " is thinking.\n");
		ft_sleep(timestamp() + 1, philo);
	}
	return (NULL);
}

void				*routine_meals(void *philo)
{
	t_philo *p;

	p = philo;
	while (1)
	{
		if (p->count_meals >= p->data->nb_needed_meals && p->global_meals == 0
			&& p->data->nb_deaths == 0)
		{
			p->data->eaten_meals++;
			p->global_meals = 1;
			if (p->data->eaten_meals >= p->data->nb_philo)
			{
				p->data->end = 1;
				write_message(p->num, p, "END OF SIMULATION.\n");
			}
		}
		usleep(1000);
	}
	return (NULL);
}

/*
**#include <sys/time.h>
**int gettimeofday(struct timeval *tv, struct timezone *tz);
**The tv argument is a struct timeval (as specified in <sys/time.h>):
**           struct timeval {
**             time_t      tv_sec;     seconds
**             suseconds_t tv_usec;    microseconds
**         };
**and gives the number of seconds and microseconds since the Epoch
*/

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
