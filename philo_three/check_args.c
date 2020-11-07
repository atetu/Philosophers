/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:38:06 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 16:52:13 by alicetetu        ###   ########.fr       */
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
				return (1);
			j++;
		}
		i++;
	}
	return (0);
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
