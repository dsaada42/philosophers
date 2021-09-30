/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:29:47 by dsaada            #+#    #+#             */
/*   Updated: 2021/09/30 17:21:39 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# define NBPHILO 5
# define NBMEAL 10
# define TTEAT 50
# define TTSLEEP 50
# define TTDIE 200
# define SUCCESS 1
# define FAILURE -1

typedef struct s_fork
{
	int		id;
	pthread_mutex_t forkex;
	int		state;
}		t_fork;

typedef struct s_philo
{
	pthread_t	philo;
	struct s_var	*v;
	int		id;
	int		nb_meal;
	long		last_meal;
	
}		t_philo;

typedef struct s_var
{
	int		nb_philo;
	int		nb_meal;
	int		tt_eat;
	int		tt_sleep;
	int		tt_die;
	t_philo		*philos;
	t_fork		*forks;
	pthread_mutex_t	print;
}		t_var;

#endif
