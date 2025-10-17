#include "philo.h"

int	main_2(t_philo **philos, t_rules *rules)
{
	int	i;

	monitor(*philos);
	i = 0;
	while (i < rules->num_philos)
		pthread_join((*philos)[i++].thread, NULL);
	i = 0;
	while (i < rules->num_philos)
		pthread_mutex_destroy(&rules->forks[i++]);
	pthread_mutex_destroy(&rules->writing);
	pthread_mutex_destroy(&rules->meal_check);
	free(rules->forks);
	free(*philos);
	return (0);
}

int main(int argc, char **argv)
{
    t_rules rules;
    t_philo *philos;
	int	i;
	
	memset(&rules, 0, sizeof(t_rules));
	if (!parse(argc, argv, &rules))
		return (1);
	if (!init(&rules, &philos))
	{
		printf("ERROR: Initialization failed.\n");
		return (1);
	}
	i = 0;
	while (i < rules.num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, (void *)routine, &philos[i]) != 0)
		{
			rules.stop = 1;
			break ;
		}
		i++;
	}
	return (main_2(&philos, &rules));
}