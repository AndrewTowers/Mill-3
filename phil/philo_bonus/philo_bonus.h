/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:52 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/13 19:40:55 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				num_philos;
	int				meals_required;
	int				stop;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	sem_t			stop_check;
	sem_t			*forks;
	sem_t			writing;
	sem_t			meal_check;
	long long		start;
}	t_rules;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	long long	last_meal_time;
	pthread_t	thread;
	t_rules		*rules;
}	t_philo;

int			parse(int argc, char **argv, t_rules *rules);
int			init(t_rules *rules, t_philo **philos);

void		*routine(t_philo *philo);

void		tk_forks(t_philo *philos);
void		drop_forks(t_philo *philos);
void		fake_sleep(long long time, t_rules *rules);
void		eat(t_philo *philos);

void		*monitor(void *arg);

int			ft_atoi(const char *nptr);
long long	timeline(void);
long long	time_lapse(long long past, long long present);
void		print_state(t_rules *rules, int id, char *str);

#endif