/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:35 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/07 09:13:05 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (philo->id % 2 == 0)
		fake_sleep(2, rules);
	while (1)
	{
		pthread_mutex_lock(&rules->stop_check);
		if (rules->stop)
		{
			pthread_mutex_unlock(&rules->stop_check);
			break ;
		}
		pthread_mutex_unlock(&rules->stop_check);
		print_state(rules, philo->id, "is thinking");
		usleep(300);
		tk_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (rules->meals_required > 0
			&& philo->meals_eaten >= rules->meals_required)
			break ;
		print_state(rules, philo->id, "is slepping");
		fake_sleep(rules->time_to_sleep, rules);
	}
	return (NULL);
}
