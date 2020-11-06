/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:49:42 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 13:06:59 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_args(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (j < ft_strlen(argv[i]))
		{
			if (argv[i][j] == '-' || argv[i][j] < 48 || argv[i][j] > 57)
				return (error("Bad arguments"));
			j++;
		}
		i++;
	}
	return (0);
}

t_data	*init_data(int argc, char **argv)
{
	t_data *data;

	if (!(data = malloc(sizeof(t_data))))
		return (error_data("Problem during memory allocation.\n"));
	memset(data, 0, sizeof(t_data));
	if (((check_args(argc, argv)) == 1)
		|| ((data->nb_philo = ft_atoi(argv[1])) == -1))
		return (exit_data(data, "Wrong arguments.\n", 0));
	if ((data->time_to_die = ft_atoull(argv[2])) <= 0)
		return (exit_data(data, "0 1 dies.\n", 0));
	data->time_to_eat = ft_atoull(argv[3]);
	data->time_to_sleep = ft_atoull(argv[4]);
	if (argc == 6)
		if ((data->nb_needed_meals = ft_atoi(argv[5])) == -1)
			return (exit_data(data, "Wrong arguments.\n", 0));
	if (pthread_mutex_init(&data->mutex_write, NULL))
		return (exit_data(data, "Problem with mutex creation.\n", 0));
	if (pthread_mutex_init(&data->mutex_died, NULL))
	{
		pthread_mutex_destroy(&data->mutex_write);
		return (exit_data(data, "Problem with mutex creation.\n", 0));
	}
	data->start = timestamp();
	return (data);
}

t_data	*init_forks(t_data *data)
{
	int i;

	i = 0;
	if (!(data->forks = malloc(sizeof(t_fork) * data->nb_philo)))
		return (exit_data(data, "Problem during memory allocation.\n", 1));
	while (i < data->nb_philo)
	{
		if (!(data->forks[i] = malloc(sizeof(t_fork))))
		{
			clear_forks(data->forks, i);
			return (exit_data(data, "Problem during memory allocation.\n", 1));
		}
		data->forks[i]->num = i;
		if (pthread_mutex_init(&data->forks[i]->mutex_fork, NULL))
		{
			clear_forks(data->forks, i);
			return (exit_data(data, "Problem during mutex creation.\n", 1));
		}
		i++;
	}
	return (data);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;

	philo = NULL;
	if (!(philo = malloc(sizeof(t_philo) * data->nb_philo)))
	{
		clear_forks(data->forks, data->nb_philo);
		return (exit_data(data, "Problem during memory allocation.\n", 1));
	}
	if (!(philo = init_each_philo(philo, data)))
		return (0);
	pthread_mutex_lock(&data->mutex_died);
	return (philo);
}

t_philo	*init_each_philo(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		philo[i].data = data;
		philo[i].num = i + 1;
		philo[i].death = data->start + philo->data->time_to_die;
		if (i == 0)
			philo[i].right_fork = data->forks[data->nb_philo - 1];
		else
			philo[i].right_fork = data->forks[i - 1];
		philo[i].left_fork = data->forks[i];
		i++;
	}
	return (philo);
}
