/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:03:11 by andtruji          #+#    #+#             */
/*   Updated: 2026/04/16 17:12:41 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_sems(void)
{
	sem_unlink("/fork_check");
	sem_unlink("/writing");
	sem_unlink("/meal_check");
}

void	close_sems(t_rules *rules)
{
	sem_close(rules->fork_check);
	sem_close(rules->writing);
}
