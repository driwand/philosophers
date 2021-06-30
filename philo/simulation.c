/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <abkssiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:09:27 by abkssiba          #+#    #+#             */
/*   Updated: 2021/06/30 16:11:27 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_health(void *data)
{
	t_philo	*p;

	p = data;
	while (1)
	{
		pthread_mutex_lock(&p->eat_lock);
		if (get_time() >= p->limit)
		{
			// *p->died = 1;
			print_stat(4, p->id);
			pthread_mutex_unlock(&g_mainlock);
			break ;
		}
		pthread_mutex_unlock(&p->eat_lock);
		usleep(100);
	}
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = data;
	pthread_create(&philo->th_check, NULL, check_health, philo);
	pthread_detach(philo->th_check);
	while (1)
	{
		pthread_mutex_lock(&g_forks[philo->right]);
		print_stat(0, philo->id);
		pthread_mutex_lock(&g_forks[philo->left]);
		print_stat(0, philo->id);
		pthread_mutex_lock(&philo->eat_lock);
		philo->limit = get_time() + g_settings.t_die;
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

void	wait_simulation(int *died, int nbr_eat)
{
	while (!*died)
	{
		if (g_settings.nbt_eat != -1)
		{
			if (g_eat_count == g_settings.total)
			{
				printf("end of simulation\n");
				break ;
			}
		}
		usleep(100);
	}
}

int	simulation(t_settings *set)
{
	int	i;

	i = 0;
	while (i < set->total)
	{
		pthread_mutex_init(&g_forks[i], NULL);
		pthread_mutex_init(&set->philos[i].eat_lock, NULL);
		set->philos[i].eat_count = 0;
		set->philos[i].id = i + 1;
		set->philos[i].right = i;
		set->philos[i].left = (i + 1) % set->total;
		i++;
	}
	g_start_time = get_time();
	i = 0;
	while (i < set->total)
	{
		set->philos[i].limit = get_time() + g_settings.t_die;
		set->philos[i].eat_count = 0;
		pthread_create(&set->philos[i].th, NULL, philosopher, &set->philos[i]);
		pthread_detach(set->philos[i].th);
		usleep(100);
		i++;
	}
	// wait_simulation(&died, set->nbt_eat);
	return (0);
}
