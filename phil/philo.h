/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:52 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/06 17:58:33 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				num_philos;
	int				meals_required;
	int				stop;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	pthread_mutex_t	stop_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
	long long		start;
}	t_rules;

typedef struct s_philo
{
	int			id;
	int			fork;
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
