/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:29:47 by dsaada            #+#    #+#             */
/*   Updated: 2021/11/08 14:20:38 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# define SUCCESS 1
# define FAILURE -1
# define MALLOC_ERROR -5

typedef struct s_fork
{
	pthread_mutex_t	forkex;
	int				state;
}		t_fork;

typedef struct s_philo
{
	pthread_t		philo;
	struct s_var	*v;
	int				id;
	int				nb_meal;
	int				state;
	int				l_fork;
	int				r_fork;
	long			last_meal;
}			t_philo;

typedef struct s_var
{
	long			s_time;
	int				nb_philo;
	int				nb_done;
	int				nb_meal;
	int				tt_eat;
	int				tt_sleep;
	int				tt_die;
	int				flag;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print;
}			t_var;

int		ft_think(t_var *v, t_philo *philo);
int		ft_eat(int ms, t_var *v, t_philo *philo);
int		ft_sleep(int ms, t_var *v, t_philo *philo);
long	get_time_ms(void);
int		get_forks(t_philo *phi, t_var *v);
int		release_forks(t_philo *phi, t_var *v);
int		init_vars(t_var *v);
void	*ft_thread(void *data);
int		parser(t_var *v, int argc, char **argv);
int		mutex_destroyer(t_var *v);

#endif
