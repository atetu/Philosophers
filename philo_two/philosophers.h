/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:37:29 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/07 14:07:42 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <errno.h>

typedef struct		s_data
{
	int					nb_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					nb_needed_meals;
	unsigned long long	start;
	int					eaten_meals;
	int					nb_deaths;
	int					nb_forks;
	int					sixth;
	int					end;
	sem_t				*sem_forks;
	sem_t				*sem_write;
	pthread_t			thread_total_meals;
}					t_data;

typedef struct		s_philo
{
	int					num;
	unsigned long long	start;
	unsigned long long	last_meal;
	unsigned long long	death;
	int					count_meals;
	int					is_eating;
	unsigned long long	dead;
	int					global_meals;
	pthread_t			thread_philo;
	pthread_t			thread_meal;
	pthread_t			control_death;
	sem_t				*sem_is_alive;
	t_data				*data;
}					t_philo;

int					error(char *str);
void				*error_data(char *str);
int					ft_strlen(char *str);
int					ft_atoi(const char *str);
unsigned long long	ft_atoull(const char *str);
void				ft_putnbr_ull(unsigned long long n);
void				ft_putstr(char *s);
int					check_args(int argc, char **argv);
t_data				*init_data(int argc, char **argv);
t_philo				*init_philo(t_data *data);
t_philo				*init_each_philo(t_philo *philo, t_data *data);
int					init_threads(t_philo *philo, int nb_philo);
int					init_threads_meals(t_philo *philo, int nb_philo);
void				*routine_philo(void *philo);
void				*routine_meals(void *philo);
void				*routine_total_meals(void *philo);
unsigned long long	timestamp(void);
int					takes_fork(int num, t_philo *philo);
int					eats(int num, t_philo *philo);
int					puts_down_forks(int num, t_philo *philo);
int					sleeps(int num, t_philo *philo);
int					write_message(int num, t_philo *philo, char *str);
void				*philo_dies(void *philo);
int					exit_philo(t_philo *philo, int n);
void				*exit_data(t_data *data, char *str);
void				clear_data(t_data *data);
void				clear_philo(t_philo *philo);
void				ft_sleep(unsigned long long end, t_philo *philo);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
