/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:04:35 by dsaada            #+#    #+#             */
/*   Updated: 2021/11/09 15:00:14 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_forks(t_philo *phi, t_var *v)
{
	pthread_mutex_lock(&(v->forks[phi->l_fork].forkex));
	v->forks[phi->l_fork].state = phi->id;
	pthread_mutex_lock(&(v->forks[phi->r_fork].forkex));
	v->forks[phi->r_fork].state = phi->id;
	pthread_mutex_lock(&(v->print));
	if (v->flag == 0)
	{
		printf("%ld %d has taken a fork\n",
			get_time_ms() - v->s_time, phi->id);
		printf("%ld %d has taken a fork\n",
			get_time_ms() - v->s_time, phi->id);
	}
	return (SUCCESS);
}

int	release_forks(t_philo *phi, t_var *v)
{
	v->forks[phi->l_fork].state = 0;
	pthread_mutex_unlock(&(v->forks[phi->l_fork].forkex));
	v->forks[phi->r_fork].state = 0;
	pthread_mutex_unlock(&(v->forks[phi->r_fork].forkex));
	return (SUCCESS);
}
