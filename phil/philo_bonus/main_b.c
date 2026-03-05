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
	int	dead;

	i = 0;
	dead = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			dead = 1;
	}
	if (dead == 1)
	{
		while (i < rules->num_philos)
		{
			kill(pids[i], SIGTERM);
			i++;
		}
	}
	close_sems(rules);
	unlink_sems();
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

void	child(t_philo *philos, t_rules *rules, pid_t *pids)
{
	pthread_t	death;
	int			i;

	i = 0;
	while (i < rules->num_philos)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			pthread_create(&death, NULL, monitor, &philos[i]);
			pthread_detach(death);
			routine(&philos[i]);
			exit(0);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_philo		*philos;
	pid_t		*pids;

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
	child(philos, &rules, pids);
	return (main_2(philos, &rules, pids));
}
