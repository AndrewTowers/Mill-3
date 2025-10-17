#include "philo.h"

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
			(*rules)->stop = 1;
	}
}

void	died(t_philo **philos, t_rules **rules)
{
	int	i;

	i = 0;
	while (i < (*rules)->num_philos)
		{
			pthread_mutex_lock(&(*rules)->meal_check);
			if (time_lapse((*philos)[i].last_meal_time, timeline()) > (*rules)->time_to_die)
			{
				print_state(*rules, (*philos)[i].id, "died");
				(*rules)->stop = 1;
				pthread_mutex_unlock(&(*rules)->meal_check);
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
	while (!rules->stop)
	{
		died(&philos, &rules);
		all_ate(&philos, &rules);
		usleep(1000);
	}
	return (NULL);
}