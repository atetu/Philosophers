/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <atetu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:28:43 by alicetetu         #+#    #+#             */
/*   Updated: 2020/06/04 18:31:04 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philo;
	int		i;

	i = 0;
	data = NULL;
	philo = NULL;
	if (argc < 5 || argc > 6)
		return (error("Wrong number of arguments.\n"));
	if (!(data = (init_data(argc, argv))))
		return (exit_philo(philo, 1));
	if (!(data = (init_forks(data))))
		return (1);
	if (!(philo = init_philo(data)))
		return (1);
	if (data->nb_needed_meals > 0)
		if (init_threads_meals(philo, data->nb_philo))
			return (1);
	if (init_threads(philo, data->nb_philo))
		return (1);
	if (pthread_mutex_lock(&data->mutex_died))
		return (exit_philo(philo, 1));
	write_message(1, philo[0], NULL);
	pthread_mutex_unlock(&data->mutex_died);
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
				return (error("Bad arguments"));
			j++;
		}
		i++;
	}
	return (0);
}
