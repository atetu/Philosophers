/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <atetu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:45:36 by alicetetu         #+#    #+#             */
/*   Updated: 2020/06/04 19:35:39 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					ft_strlen(char *str)
{
	int nb;

	nb = 0;
	while (*str)
	{
		nb++;
		str++;
	}
	return (nb);
}

int					ft_atoi(const char *str)
{
	unsigned int		nb;

	nb = 0;
	while (*str && (*str == '\t' || *str == '\n' || *str == '\v' ||
		*str == '\f' || *str == '\r' || *str == ' '))
		str++;
	while ((*str >= 48 && *str <= 57) && *str)
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

unsigned long long	ft_atoull(const char *str)
{
	unsigned long long		nb;

	nb = 0;
	while (*str && (*str == '\t' || *str == '\n' || *str == '\v' ||
		*str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (*str == '+')
		str++;
	while ((*str >= 48 && *str <= 57) && *str)
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	return (nb);
}

void				ft_putnbr_ull(unsigned long long n)
{
	if (n > 9)
	{
		ft_putnbr_ull(n / 10);
		ft_putnbr_ull(n % 10);
	}
	else
	{
		n = n + 48;
		write(1, &n, 1);
	}
}

void				ft_putstr(char *s)
{
	if (!s)
		return ((void)(NULL));
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}
