/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:32 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/06 19:25:22 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tk_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	pthread_mutex_lock(&rules->forks[philos->fork]);
	print_state(rules, philos->id, "has taken a fork");
}

void	drop_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	pthread_mutex_unlock(&rules->forks[philos->fork]);
}

void	fake_sleep(long long time, t_rules *rules)
{
	long long	start;

	start = timeline();
	pthread_mutex_lock(&rules->stop_check);
	while (!rules->stop)
	{
		if (time_lapse(start, timeline()) >= time)
			break ;
		usleep(500);
	}
	pthread_mutex_unlock(&rules->stop_check);
}

void	eat(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	pthread_mutex_lock(&rules->meal_check);
	philos->last_meal_time = timeline();
	pthread_mutex_unlock(&rules->meal_check);
	print_state(rules, philos->id, "is eating");
	fake_sleep(rules->time_to_eat, rules);
	philos->meals_eaten++;
}