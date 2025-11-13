/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:26 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/13 19:16:31 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse(int argc, char **argv, t_rules *rules)
{
	if (argc < 5 || argc > 6)
	{
		printf("ERROR: Incorrect number of arguments.\n");
		return (0);
	}
	rules->num_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->meals_required = ft_atoi(argv[5]);
	rules->stop = 0;
	rules->start = timeline();
	return (1);
}

int	init(t_rules *rules, t_philo **philos)
{
	int	i;

	rules->forks = malloc(sizeof(sem_t) * rules->num_philos);
	if (!rules->forks)
		return (0);
	i = 0;
	while (i < rules->num_philos)
		sem_open(&rules->forks[i++], O_CREAT, 0644, 1);
	sem_open(&rules->stop_check, O_CREAT, 0644, 1);
	sem_open(&rules->writing, O_CREAT, 0644, 1);
	sem_open(&rules->meal_check, O_CREAT, 0644, 1);
	*philos = malloc(sizeof(t_philo) * rules->num_philos);
	if (!*philos)
		return (0);
	i = 0;
	while (i < rules->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = i;
		(*philos)[i].right_fork = (i + 1) % rules->num_philos;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = rules->start;
		(*philos)[i++].rules = rules;
	}
	return (1);
}
