/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:35 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/03 13:16:47 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		print_state(philo->rules, philo->id, "is thinking");
		tk_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (philo->rules->meals_required > 0
			&& philo->meals_eaten >= philo->rules->meals_required)
			exit(0);
		print_state(philo->rules, philo->id, "is sleeping");
		fake_sleep(philo->rules->time_to_sleep, philo->rules);
	}
	return (NULL);
}
