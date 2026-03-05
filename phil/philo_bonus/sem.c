#include "philo_bonus.h"

void    unlink_sems(void)
{
    sem_unlink("/fork_check");
    sem_unlink("/writing");
    sem_unlink("/meal_check");
}

void    close_sems(t_rules *rules)
{
    sem_close(rules->fork_check);
    sem_close(rules->writing);
    sem_close(rules->meal_check);
}

