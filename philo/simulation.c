/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <abkssiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:09:27 by abkssiba          #+#    #+#             */
/*   Updated: 2021/06/19 16:46:16 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_health(void *data)
{
	t_philo	*p;

	p = data;
	while (1)
	{
		if (get_time() >= p->limit)
		{
			*p->died = 1;
			print_stat(4, p->id);
			break ;
		}
	}
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = data;
	philo->limit = get_time() + g_settings.t_die;
	philo->eat_count = 0;
	pthread_create(&philo->th_check, NULL, check_health, philo);
	pthread_detach(philo->th_check);
	while (1)
	{
		pthread_mutex_lock(&g_forks[philo->right]);
		pthread_mutex_lock(&g_forks[philo->left]);
		philo->limit = get_time() + g_settings.t_die;
		print_stat(1, philo->id);
		eat_count(philo);
		usleep(g_settings.t_eat * 1000);
		pthread_mutex_unlock(&g_forks[philo->right]);
		pthread_mutex_unlock(&g_forks[philo->left]);
		print_stat(2, philo->id);
		usleep(g_settings.t_sleep * 1000);
		print_stat(3, philo->id);
	}
	return (NULL);
}

void	wait_simulation(int *died)
{
	while (!*died)
	{
		if (g_settings.nbt_eat != -1)
		{
			if (g_eat_count == g_settings.total - 1)
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
	int	died;

	i = 0;
	died = 0;
	while (i < set->total)
	{
		pthread_mutex_init(&g_forks[i], NULL);
		set->phlios[i].id = i + 1;
		set->phlios[i].right = i;
		set->phlios[i].left = (i + 1) % 5;
		set->phlios[i].died = &died;
		i++;
	}
	g_start_time = get_time();
	i = 0;
	while (i < set->total)
	{
		pthread_create(&set->phlios[i].th, NULL, philosopher, &set->phlios[i]);
		pthread_detach(set->phlios[i].th);
		i = i + 1;
	}
	wait_simulation(&died);
	return (0);
}
