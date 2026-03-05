/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:32 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/03 12:20:26 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	tk_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	sem_wait(rules->fork_check);
	print_state(rules, philos->id, "has taken a fork");
	sem_wait(rules->fork_check);
	print_state(rules, philos->id, "has taken a fork");
}

void	drop_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	sem_post(rules->fork_check);
	sem_post(rules->fork_check);
}

void	fake_sleep(long long time, t_rules *rules)
{
	long long	start;

	(void)rules;
	start = timeline();
	while (time_lapse(start, timeline()) < time)
		usleep(100);
}

void	eat(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	sem_wait(rules->meal_check);
	philos->last_meal_time = timeline();
	philos->meals_eaten++;
	sem_post(rules->meal_check);
	print_state(rules, philos->id, "is eating");
	fake_sleep(rules->time_to_eat, rules);
}
