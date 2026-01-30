/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:35 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/20 18:49:02 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		fake_sleep(1, philo->rules);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->stop_check);
		if (philo->rules->stop)
		{
			pthread_mutex_unlock(&philo->rules->stop_check);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->stop_check);
		print_state(philo->rules, philo->id, "is thinking");
		fake_sleep(philo->rules->time_to_eat / 2, philo->rules);
		tk_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (philo->rules->meals_required > 0
			&& philo->meals_eaten >= philo->rules->meals_required)
			break ;
		print_state(philo->rules, philo->id, "is sleeping");
		fake_sleep(philo->rules->time_to_sleep, philo->rules);
	}
	return (NULL);
}
