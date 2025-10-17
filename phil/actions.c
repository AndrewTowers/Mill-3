#include "philo.h"

void	tk_forks(t_philo *philos)
{
	t_rules *rules;

	rules = philos->rules;
	pthread_mutex_lock(&rules->forks[philos->fork]);
	print_state(rules, philos->id, "has taken a fork");
}

void	drop_forks(t_philo *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	pthread_mutex_unlock(&rules->forks[philos->fork]);
}

void	fake_sleep(long long time, t_rules *rules)
{
	long long	start;

	start = timeline();
	while (!rules->stop)
	{
		if (time_lapse(start, timeline()) >= time)
			break ;
		usleep(500);
	}
}

void	eat(t_philo *philos)
{
	t_rules *rules;

	rules = philos->rules;
	pthread_mutex_lock(&rules->meal_check);
	philos->last_meal_time = timeline();
	pthread_mutex_unlock(&rules->meal_check);
	print_state(rules, philos->id, "is eating");
	fake_sleep(rules->time_to_eat, rules);
	philos->meals_eaten++;
}