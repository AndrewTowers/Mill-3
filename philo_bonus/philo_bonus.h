/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:52 by andtruji          #+#    #+#             */
/*   Updated: 2026/05/13 11:50:55 by andtruji         ###   ########.fr       */
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
# include <sys/wait.h>

typedef struct s_rules
{
	int				num_philos;
	int				meals_required;
	int				stop;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	sem_t			*fork_check;
	sem_t			*writing;
	sem_t			*meals_check;
	long long		start;
}	t_rules;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	int			status;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	long long	last_meal_time;
	t_rules		*rules;
}	t_philo;

int			parse(int argc, char **argv, t_rules *rules);
int			init(t_rules *rules, t_philo **philos);

void		*routine(void *arg);

void		tk_forks(t_philo *philos);
void		drop_forks(t_philo *philos);
void		fake_sleep(long long time, t_rules *rules);
void		eat(t_philo *philos);

void		*monitor(void *arg);

int			ft_atoi(const char *nptr);
long long	timeline(void);
long long	time_lapse(long long past, long long present);
void		print_state(t_rules *rules, int id, char *str);

void		unlink_sems(void);
void		close_sems(t_rules *rules);

#endif