/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <atetu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:49:42 by alicetetu         #+#    #+#             */
/*   Updated: 2020/06/05 17:40:27 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*init_data(int argc, char **argv)
{
	t_data *data;

	if (!(data = malloc(sizeof(t_data))))
		return (error_data("Problem during memory allocation.\n"));
	memset(data, 0, sizeof(t_data));
	if ((check_args(argc, argv)) == 1)
		return (exit_data(data, "Wrong arguments.\n"));
	if ((data->nb_philo = ft_atoi(argv[1])) == -1)
		return (exit_data(data, "Wrong arguments.\n"));
	data->time_to_die = ft_atoull(argv[2]) * 1000;
	data->time_to_eat = ft_atoull(argv[3]) * 1000;
	data->time_to_sleep = ft_atoull(argv[4]) * 1000;
	if (argc == 6)
		if ((data->nb_needed_meals = ft_atoi(argv[5])) == -1)
			return (exit_data(data, "Wrong arguments.\n"));
//	pthread_mutex_init(&data->mutex_write, NULL);
//	pthread_mutex_init(&data->mutex_died, NULL);
	return (data);
}

t_data	*init_forks(t_data *data)
{
/*	int i;

	i = 0;
	if (!(data->forks = malloc(sizeof(t_fork) * data->nb_philo)))
		return (exit_data(data, "Problem during memory allocation.\n"));
	while (i < data->nb_philo)
	{
		if (!(data->forks[i] = malloc(sizeof(t_fork))))
		{
			clear_forks(data->forks, i);
			return (exit_data(data, "Problem during memory allocation.\n"));
		}
		data->forks[i]->num = i;
		pthread_mutex_init(&data->forks[i]->mutex_fork, NULL);
		i++;
	}*/
	data->sem_forks = sem_open("forks", O_CREAT, S_IRWXU, data->nb_philo);
	return (data);
}

t_philo	**init_philo(t_data *data)
{
	int		i;
	t_philo	**philo;

	i = 0;
	philo = NULL;
	if (!(philo = malloc(sizeof(t_philo) * data->nb_philo)))
	{
//		clear_forks(data->forks, data->nb_philo);
//		return (exit_data(data, "Problem during memory allocation.\n"));
	}
	if (!(philo = init_each_philo(philo, data)))
		return (NULL);
//	pthread_mutex_lock(&data->mutex_died);
	return (philo);
}

t_philo	**init_each_philo(t_philo **philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (!(philo[i] = malloc(sizeof(t_philo))))
		{
//			clear_philo(philo, i);
//			clear_forks(data->forks, data->nb_philo);
			return (exit_data(data, "Problem during memory allocation\n"));
		}
		memset(philo[i], 0, sizeof(t_philo));
		philo[i]->data = data;
		philo[i]->num = i + 1;
//		if (i == 0)
//			philo[i]->right_fork = data->forks[data->nb_philo - 1];
//		else
//			philo[i]->right_fork = data->forks[i - 1];
//		philo[i]->left_fork = data->forks[i];
//		pthread_mutex_init(&philo[i]->mutex_alive, NULL);
		i++;
	}
	return (philo);
}
