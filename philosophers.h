/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:29:47 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/01 14:21:19 by dsaada           ###   ########.fr       */
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
# define TTEAT 200
# define TTSLEEP 200
# define TTDIE 500
# define SUCCESS 1
# define FAILURE -1
# define MALLOC_ERROR -5

typedef struct s_fork
{
	pthread_mutex_t forkex;
	int		state;
}		t_fork;

typedef struct s_philo
{
	pthread_t	philo;
	struct s_var	*v;
	int		id;
	int		nb_meal;
	int		state;
	int		l_fork;
	int		r_fork;
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
