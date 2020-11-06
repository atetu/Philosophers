/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:26:53 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 11:02:33 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_threads_meals(t_philo *philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&(philo[i].thread_meal), NULL, &routine_meals,
					(void*)&philo[i]))
		{
			exit_philo(philo, 1);
			return (error("Problem during thread creation.\n"));
		}
		i++;
	}
	if (pthread_create(&philo[0].data->thread_total_meals, NULL,
				&routine_total_meals, (void*)(&philo[0])))
	{
		exit_philo(philo, 1);
		return (error("Problem during thread creation.\n"));
	}
	return (0);
}

int		init_threads(t_philo *philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i].thread_philo, NULL, &routine_philo,
					(void*)&philo[i]))
		{
			exit_philo(philo, 1);
			return (error("Problem during thread creation.\n"));
		}
		i++;
		ft_sleep(timestamp() + 2, philo);
	}
	return (0);
}

void	*philo_action(void *philo)
{
	t_philo	*p;

	p = philo;
	while (p->dead == 0 && p->data->nb_deaths == 0)
	{
		if (!(takes_fork(p->num, p)))
			return (NULL);
		if (!(eats(p->num, p)))
			return (NULL);
		if (!(puts_down_forks(p->num, p)))
			return (NULL);
		if (!(sleeps(p->num, p)))
			return (NULL);
		if (!(write_message(p->num, p, " is thinking.\n")))
			return (NULL);
	}
	return (NULL);
}

void	*philo_dies(void *philo)
{
	t_philo				*p;
	unsigned long long	t;

	p = philo;
	while (1)
	{
		t = timestamp();
		if (p->death <= t && !p->is_eating)
		{
			p->data->end = 1;
			write_message(p->num, p, " dies.\n");
			pthread_mutex_unlock(&p->data->mutex_died);
			return ((void *)1);
		}
		if (p->data->nb_deaths == 1)
			return ((void *)1);
		t = 0;
	}
}
