/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:29 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/12 16:34:50 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;

	philos = (t_philo *)arg;
	rules = philos->rules;
	while (1)
	{
		sem_wait(rules->meal_check);
		if (time_lapse(philos->last_meal_time, timeline()) > rules->time_to_die)
		{
			sem_post(rules->meal_check);
			sem_wait(rules->writing);
			printf("%lld %d died\n", timeline() - rules->start, philos->id);
			return (NULL);
		}
		sem_post(rules->meal_check);
		usleep(50);
	}
	return (NULL);
}
