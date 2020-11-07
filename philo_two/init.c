/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:49:42 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 11:25:58 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t	*create_sem(char *name, int n)
{
	sem_t	*sem;

	sem = NULL;
	sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, n);
	while (sem == SEM_FAILED && errno == EEXIST)
	{
		sem_unlink(name);
		errno = 0;
		sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, n);
	}
	return (sem);
}

int		check_sixth_arg(int argc, char **argv, t_data *data)
{
	if (argc == 6)
	{
		if ((data->nb_needed_meals = ft_atoi(argv[5])) <= 0)
			return (0);
	}
	else
		data->nb_needed_meals = -1;
	return (1);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (!(data = malloc(sizeof(t_data))))
		return (error_data("Problem during memory allocation.\n"));
	memset(data, 0, sizeof(t_data));
	if (((check_args(argc, argv)) == 1)
		|| ((data->nb_philo = ft_atoi(argv[1])) == -1))
		return (exit_data(data, "Wrong arguments.\n"));
	data->nb_forks = data->nb_philo;
	if ((data->time_to_die = ft_atoull(argv[2])) <= 0
		|| (data->time_to_eat = ft_atoull(argv[3])) <= 0
		|| (data->time_to_sleep = ft_atoull(argv[4]) <= 0))
		return (exit_data(data, "Wrong arguments.\n"));
	if (!check_sixth_arg(argc, argv, data))
		return (exit_data(data, "Wrong arguments.\n"));
	data->sem_forks = create_sem("forks", data->nb_philo);
	data->sem_write = create_sem("write", 1);
	data->start = timestamp();
	return (data);
}

t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = NULL;
	if (!(philo = malloc(sizeof(t_philo) * data->nb_philo)))
		return (exit_data(data, "Problem during memory allocation.\n"));
	philo = init_each_philo(philo, data);
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
		i++;
	}
	return (philo);
}
