/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:29 by andtruji          #+#    #+#             */
/*   Updated: 2026/05/13 11:52:35 by andtruji         ###   ########.fr       */
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
		if (time_lapse(philos->last_meal_time, timeline()) > rules->time_to_die)
		{
			sem_wait(rules->writing);
			printf("%lld %d died\n", timeline() - rules->start, philos->id);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}
