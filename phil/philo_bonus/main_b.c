/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:19 by andtruji          #+#    #+#             */
/*   Updated: 2025/11/20 17:32:16 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main_2(t_philo **philos, t_rules *rules)
{
	int	i;

	monitor(*philos);
	i = 0;
	while (i < rules->num_philos)
	{
		wait(NULL);
		i++;
	}
	i = 0;
	while (i < rules->num_philos)
		sem_unlink(&rules->forks[i++]);
	sem_unlink("/stop_check");
	sem_unlink("/writing");
	sem_unlink("/meal_check");
	free(rules->forks);
	free(*philos);
	return (0);
}

int	is_one(t_rules rules)
{
	printf("0 1 has taken a fork\n");
	printf("%lld 1 died\n", rules.time_to_die);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;
	pid_t	*pids;
	int		i;

	memset(&rules, 0, sizeof(t_rules));
	if (!parse(argc, argv, &rules))
		return (1);
	if (rules.num_philos == 1)
		return (is_one(rules));
	if (!init(&rules, &philos))
		return (1);
	pids = malloc(sizeof(pid_t) * rules.num_philos);
	if (!pids)
		return (1);
	i = 0;
	while (i < rules.num_philos)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			routine(&philos[i]);
			exit(0);
		}
		i++;
	}
	return (main_2(&philos, &rules));
}
