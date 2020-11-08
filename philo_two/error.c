/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:43:01 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 18:45:14 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
