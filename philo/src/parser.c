/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:35:57 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/12 14:52:40 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_is_ws(char c)
{
	if (c == '\t' || c == '\v' || c == '\n'
		|| c == '\r' || c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}

static int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	i = 0;
	while (nptr[i] && (ft_is_ws(nptr[i]) == 1))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

static int	check_arg(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (FAILURE);
	}
	return (SUCCESS);
}

int	parser(t_var *v, int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (FAILURE);
	while (++i < argc)
	{
		if (check_arg(argv[i]) == FAILURE)
			return (FAILURE);
	}
	v->nb_philo = ft_atoi(argv[1]);
	if (v->nb_philo < 1)
		return (FAILURE);
	v->tt_die = ft_atoi(argv[2]);
	v->tt_eat = ft_atoi(argv[3]);
	v->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		v->nb_meal = ft_atoi(argv[5]);
	else
		v->nb_meal = -1;
	return (SUCCESS);
}
