/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:32 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/13 19:52:52 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	tk_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	sem_wait(rules->forks);
	print_state(rules, philos->id, "has taken a fork");
	sem_wait(rules->forks);
	print_state(rules, philos->id, "has taken a fork");
}

void	drop_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	sem_post(&rules->forks);
	sem_post(&rules->forks);
}

void	fake_sleep(long long time, t_rules *rules)
{
	long long	start;

	start = timeline();
	sem_wait(&rules->stop_check);
	while (!rules->stop)
	{
		if (time_lapse(start, timeline()) >= time)
			break ;
		usleep(100);
	}
	sem_post(&rules->stop_check);
}

void	eat(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	sem_wait(&rules->meal_check);
	philos->last_meal_time = timeline();
	sem_post(&rules->meal_check);
	print_state(rules, philos->id, "is eating");
	fake_sleep(rules->time_to_eat, rules);
	philos->meals_eaten++;
}
