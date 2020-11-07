/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:12:18 by atetu             #+#    #+#             */
/*   Updated: 2020/11/07 16:36:48 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		check_program_end(int num, t_philo *philo, char *str)
{
	unsigned long long	t;

	if (!(ft_strncmp(str, "END OF SIMULATION", 17)))
	{
		ft_putstr(str);
		ft_sleep(timestamp() + 1, philo);
		return (1);
	}
	if (!(ft_strncmp(str, " dies.\n", 7)))
	{
		t = (timestamp() - philo->data->start);
		ft_putnbr_ull(t);
		write(1, " ", 1);
		ft_putnbr_ull((unsigned long long)(num));
		ft_putstr(str);
		philo->data->nb_deaths = 1;
		ft_sleep(timestamp() + 1, philo);
		return (1);
	}
	return (0);
}

static int		check_num_str(int num, char *str)
{
	if (num == 0)
	{
		ft_putstr(str);
		return (1);
	}
	if (!str)
	{
		ft_putstr("GAME OVER\n");
		return (1);
	}
	return (0);
}

int				write_message(int num, t_philo *philo, char *str)
{
	unsigned long long	t;

	sem_wait(philo->data->sem_write);
	if (!philo->data->nb_deaths)
	{
		if (philo->data->end)
		{
			if (check_num_str(num, str))
				return (0);
			if (check_program_end(num, philo, str))
				return (0);
		}
		if (!philo->data->nb_deaths)
		{
			t = (timestamp() - philo->data->start);
			ft_putnbr_ull(t);
			write(1, " ", 1);
			ft_putnbr_ull((unsigned long long)(num));
			ft_putstr(str);
		}
	}
	else
		return (0);
	sem_post(philo->data->sem_write);
	return (1);
}

int				error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

void			*error_data(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (0);
}
