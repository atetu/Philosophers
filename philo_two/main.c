/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:28:43 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/04 17:08:44 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void __attribute__((destructor))
// 	on_stop(void)
// {
// 	while (1)
// 		;
// }

void	wait_death_eaten_meals(t_data *data)
{
	if (data->nb_needed_meals != -1)
	{
		while (data->nb_deaths == 0 && data->eaten_meals < data->nb_philo)
		{
			if (data->eaten_meals < data->nb_philo)
				usleep(2000);
		}
	}
	else
	{
		while (data->nb_deaths == 0)
		{
		}
	}
}

int		main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	i = 0;
	data = NULL;
	philo = NULL;
	if (argc < 5 || argc > 6)
		return (error("Wrong number of arguments.\n"));
	if (!(data = (init_data(argc, argv))))
		return (1);
	sem_unlink("forks");
	sem_unlink("write");
	if (!(philo = init_philo(data)))
		return (1);
	if (init_threads(philo, data->nb_philo))
		return (1);
	if (data->nb_needed_meals != -1)
	{
		if (init_threads_meals(philo, data->nb_philo))
			return (1);
	}
	wait_death_eaten_meals(data);
	return (exit_philo(philo, 0));
}

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
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
