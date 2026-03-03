/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:55:19 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/03 13:42:22 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main_2(t_philo *philos, t_rules *rules, pid_t *pids)
{
	int	i;
	int	status;

	(void)rules;
	monitor(philos);
	i = 0;
	while (i < rules->num_philos)
		waitpid(pids[i++], &status, 0);
	i = 0;
	sem_close(rules->fork_check);
	sem_unlink("/fork_check");
	sem_close(rules->stop_check);
	sem_unlink("/stop_check");
	sem_close(rules->writing);
	sem_unlink("/writing");
	sem_close(rules->meal_check);
	sem_unlink("/meal_check");
	free(philos);
	free(pids);
	return (0);
}

int	is_one(t_rules rules)
{
	printf("0 1 has taken a fork\n");
	usleep(1000 * rules.time_to_die);
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
	return (main_2(philos, &rules, pids));
}
