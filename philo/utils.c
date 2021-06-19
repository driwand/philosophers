/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <abkssiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:39:19 by abkssiba          #+#    #+#             */
/*   Updated: 2021/06/19 18:24:00 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	struct timeval	v;

	gettimeofday(&v, NULL);
	return ((v.tv_sec * 1000) + (v.tv_usec / 1000));
}

void	print_stat(int stat, int id)
{
	int		time;
	char	*check;

	time = get_time() - g_start_time;
	pthread_mutex_lock(&g_io_lock);
	if (stat == 0)
		check = "has taken a fork";
	else if (stat == 1)
		check = "is eating";
	else if (stat == 2)
		check = "is sleeping";
	else if (stat == 3)
		check = "is thinking";
	else
		check = "died";
	printf("%d %d %s\n", time, id, check);
	if (stat <= 3)
		pthread_mutex_unlock(&g_io_lock);
}

void	eat_count(t_philo *philo)
{
	philo->eat_count++;
	if (g_settings.nbt_eat != -1)
	{
		if (philo->eat_count == 5)
			g_eat_count += 1;
	}
}
