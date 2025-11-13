/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:29 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/13 18:16:39 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	all_ate(t_philo **philos, t_rules **rules)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	if ((*rules)->meals_required > 0)
	{
		while (i < (*rules)->num_philos)
		{
			if ((*philos)[i].meals_eaten < (*rules)->meals_required)
			{
				all_ate = 0;
				break ;
			}
			i++;
		}
		if (all_ate)
		{
			pthread_mutex_lock(&(*rules)->stop_check);
			(*rules)->stop = 1;
			pthread_mutex_unlock(&(*rules)->stop_check);
		}
	}
}

void	died(t_philo **philos, t_rules **rules)
{
	int	i;

	i = 0;
	while (i < (*rules)->num_philos)
	{
		pthread_mutex_lock(&(*rules)->meal_check);
		if (time_lapse((*philos)[i].last_meal_time,
			timeline()) > (*rules)->time_to_die)
		{
			print_state(*rules, (*philos)[i].id, "died");
			pthread_mutex_lock(&(*rules)->stop_check);
			(*rules)->stop = 1;
			pthread_mutex_unlock(&(*rules)->stop_check);
			pthread_mutex_unlock(&(*rules)->meal_check);
			break ;
		}
		pthread_mutex_unlock(&(*rules)->meal_check);
		i++;
	}
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (1)
	{
		pthread_mutex_lock(&rules->stop_check);
		if (rules->stop)
		{
			pthread_mutex_unlock(&rules->stop_check);
			break ;
		}
		pthread_mutex_unlock(&rules->stop_check);
		died(&philos, &rules);
		all_ate(&philos, &rules);
		usleep(1000);
	}
	return (NULL);
}
