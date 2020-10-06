#include "philosophers.h"

void write_message(int num, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_write);
	if (num == 0)
	{
		ft_putstr(str);
		usleep(1000);
	}
	if (!str)
	{
		ft_putstr("GAME OVER\n");
		usleep(1000);
	}
	else
	{
		ft_putnbr_ull(timestamp());
		write (1, " ", 1);
		ft_putnbr_ull((unsigned long long)(num));
		ft_putstr(str);
	}
	pthread_mutex_unlock(&philo->data->mutex_write);
}

int		error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

void	*error_data(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (0);
}
