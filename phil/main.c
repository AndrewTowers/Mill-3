/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:19 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/06 19:18:34 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_2(t_philo **philos, t_rules *rules)
{
	int	i;

	monitor(*philos);
	i = 0;
	while (i < rules->num_philos)
		pthread_detach((*philos)[i++].thread);
		//pthread_join((*philos)[i++].thread, NULL);
	i = 0;
	while (i < rules->num_philos)
		pthread_mutex_destroy(&rules->forks[i++]);
	pthread_mutex_destroy(&rules->writing);
	pthread_mutex_destroy(&rules->meal_check);
	pthread_mutex_destroy(&rules->stop_check);
	free(rules->forks);
	free(*philos);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;
	int		i;

	memset(&rules, 0, sizeof(t_rules));
	if (!parse(argc, argv, &rules))
		return (1);
	if (!init(&rules, &philos))
		return (1);
	i = 0;
	while (i < rules.num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL,
				(void *)routine, &philos[i]) != 0)
		{
			pthread_mutex_lock(&philos->rules->stop_check);
			rules.stop = 1;
			pthread_mutex_unlock(&philos->rules->stop_check);
			break ;
		}
		i++;
	}
	return (main_2(&philos, &rules));
}
