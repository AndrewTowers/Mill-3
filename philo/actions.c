/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:32 by andtruji          #+#    #+#             */
/*   Updated: 2026/05/13 11:39:53 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tk_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	if (philos->id % 2 == 0)
	{
		usleep(200);
		pthread_mutex_lock(&rules->forks[philos->left_fork]);
		print_state(rules, philos->id, "has taken a fork");
		pthread_mutex_lock(&rules->forks[philos->right_fork]);
		print_state(rules, philos->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&rules->forks[philos->right_fork]);
		print_state(rules, philos->id, "has taken a fork");
		pthread_mutex_lock(&rules->forks[philos->left_fork]);
		print_state(rules, philos->id, "has taken a fork");
	}
}

void	drop_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	pthread_mutex_unlock(&rules->forks[philos->left_fork]);
	pthread_mutex_unlock(&rules->forks[philos->right_fork]);
}

void	fake_sleep(long long time, t_rules *rules)
{
	long long	start;

	start = timeline();
	while (1)
	{
		pthread_mutex_lock(&rules->stop_check);
		if (rules->stop)
		{
			pthread_mutex_unlock(&rules->stop_check);
			break ;
		}
		pthread_mutex_unlock(&rules->stop_check);
		if (time_lapse(start, timeline()) >= time)
			break ;
		usleep(500);
	}
}

void	eat(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	pthread_mutex_lock(&rules->meal_check);
	philos->last_meal_time = timeline();
	philos->meals_eaten++;
	pthread_mutex_unlock(&rules->meal_check);
	print_state(rules, philos->id, "is eating");
	fake_sleep(rules->time_to_eat, rules);
}
