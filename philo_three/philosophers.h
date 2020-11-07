/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:37:29 by alicetetu         #+#    #+#             */
/*   Updated: 2020/11/06 17:09:40 by alicetetu        ###   ########.fr       */
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
# include <signal.h>

#include <stdio.h> //a eneleber

typedef struct			s_data
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
	sem_t				*sem_dead;
	sem_t				*sem_meals;
	pthread_t			thread_total_meals;
}						t_data;

typedef struct			s_philo
{
	int					num;
	unsigned long long	start;
	unsigned long long	last_meal;
	unsigned long long	death;
	int					count_meals;
	int					is_eating;
	unsigned long long	dead;
	int					global_meals;
	pid_t				process;
	pthread_t			thread_philo;
	pthread_t			thread_meal;
	pthread_t			control_death;
	pthread_t			thread_actions;
	pthread_t			thread_monitor_meals_main_program;
	t_data				*data;
}						t_philo;

int						error(char *str);
void					*error_data(char *str);
int						ft_strlen(char *str);
int						ft_atoi(const char *str);
unsigned long long		ft_atoull(const char *str);
void					ft_putnbr_ull(unsigned long long n);
void					ft_putstr(char *s);
int						check_args(int argc, char **argv);
t_data					*init_data(int argc, char **argv);
t_philo					*init_philo(t_data *data);
t_philo					*init_each_philo(t_philo *philo, t_data *data);
void					init_process(t_philo *philo, int nb_philo);
int						init_threads_meals(t_philo *philo);
void					*routine_philo(t_philo *philo);
void					*routine_meals(void *philo);
void					*routine_total_meals(void *philo);

void					*routine_wait_pids(void *pid_philo);
void					*monitor_each_pid(void *pid_philo);
unsigned long long		timestamp(void);
void					takes_fork(int num, t_philo *philo);
void					eats(int num, t_philo *philo);
void					puts_down_forks(int num, t_philo *philo);
void					sleeps(int num, t_philo *philo);
void					write_message(int num, t_philo *philo, char *str);
int						exit_philo_data(t_philo *philo, int n);
int						exit_philo_data_array(t_philo *philo, pthread_t *array_wait_pid, int n);
void					*exit_data(t_data *data, char *str);
void					clear_data(t_data *data);
void					clear_philo(t_philo *philo);
void					clear_array_wait_pid(pthread_t	*array_wait_pid);
void					ft_sleep(unsigned long long end, t_philo *philo);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
pthread_t				*thread_wait_pid(t_philo *philo);
void					*monitor_global_death(void *data);
void					*monitor_global_meals(void *philo);
void					*monitor_meals_main_program(void *philo);
sem_t					*create_sem(char *name, int n);
int						thread_wait_death_or_meals(t_data *data,
							t_philo *philo);
void					*process_wait_meals(void *philo);
int						check_sixth_arg(int argc, char **argv, t_data *data);
#endif
