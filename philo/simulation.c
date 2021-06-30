/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <abkssiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:09:27 by abkssiba          #+#    #+#             */
/*   Updated: 2021/06/30 20:27:51 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_health(void *data)
{
	t_philo	*p;

	p = data;
	while (1)
	{
		if ((get_time() - p->limit) > g_settings.t_die)
		{
			pthread_mutex_lock(&p->eat_lock);
			print_stat(4, p->id);
			pthread_mutex_unlock(&g_mainlock);
			break ;
		}
		// pthread_mutex_unlock(&p->eat_lock);
		usleep(100);
	}
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;
	pthread_t	th;

	philo = data;
	philo->limit = get_time();
	pthread_create(&th, NULL, &check_health, philo);
	pthread_detach(th);
	while (1)
	{
		pthread_mutex_lock(&g_forks[philo->right]);
		print_stat(0, philo->id);
		pthread_mutex_lock(&g_forks[philo->left]);
		print_stat(0, philo->id);
		pthread_mutex_lock(&philo->eat_lock);
		philo->limit = get_time();
		print_stat(1, philo->id);
		eat_count(philo);
		usleep(g_settings.t_eat * 1000);
		pthread_mutex_unlock(&g_forks[philo->right]);
		pthread_mutex_unlock(&g_forks[philo->left]);
		pthread_mutex_unlock(&philo->eat_lock);
		print_stat(2, philo->id);
		usleep(g_settings.t_sleep * 1000);
		print_stat(3, philo->id);
	}
	return (NULL);
}

int	simulation(t_settings *set)
{
	int	i;

	i = 0;
	while (i < set->total)
	{
		pthread_mutex_init(&set->philos[i].eat_lock, NULL);
		set->philos[i].eat_count = 0;
		set->philos[i].id = i + 1;
		set->philos[i].right = i;
		set->philos[i].left = (i + 1) % set->total;
		i++;
	}
	g_start_time = get_time();
	pthread_mutex_lock(&g_mainlock);
	i = 0;
	while (i < set->total)
	{
		pthread_create(&set->philos[i].thread, NULL, &philosopher, &set->philos[i]);
		pthread_detach(set->philos[i].thread);
		usleep(100);
		i++;
	}
	return (0);
}
