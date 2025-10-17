#include "philo.h"

void	*routine(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (philo->id % 2 == 0)
		fake_sleep(2, rules);
	while(!rules->stop)
	{
		tk_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (rules->meals_required > 0 && philo->meals_eaten >= rules->meals_required)
			break ;
		print_state(rules, philo->id, "is_slepping");
		fake_sleep(rules->time_to_sleep, rules);
		print_state(rules, philo->id, "is_thinking");
	}
	return (NULL);
}
