/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:28:43 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 13:22:00 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void __attribute__((destructor))
// 	on_stop(void)
// {
// 	while (1)
// 		;
// }

int		main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	philo = NULL;
	if (argc < 5 || argc > 6)
		return (error("Wrong number of arguments.\n"));
	if (!(data = (init_data(argc, argv))))
		return (1);
	if (!(data = (init_forks(data))))
		return (1);
	if (!(philo = init_philo(data)))
		return (1);
	if (init_threads(philo, data->nb_philo))
		return (1);
	if (data->nb_needed_meals > 0)
		if (init_threads_meals(philo, data->nb_philo))
			return (1);
	pthread_mutex_lock(&data->mutex_died);
	pthread_mutex_unlock(&data->mutex_died);
	return (exit_philo(philo, 0));
}
