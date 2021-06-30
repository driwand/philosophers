/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <abkssiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:25:33 by abkssiba          #+#    #+#             */
/*   Updated: 2021/06/30 20:24:19 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init(void)
{
	int i;

	i = 0;
	g_eat_count = 0;
	g_forks = malloc(g_settings.total * sizeof(pthread_mutex_t));
	g_settings.philos = malloc(g_settings.total * sizeof(t_philo));
	while (i < g_settings.total)
		pthread_mutex_init(&g_forks[i++], NULL);	
	pthread_mutex_init(&g_io_lock, NULL);
	pthread_mutex_init(&g_mainlock, NULL);
}

void destroy(void)
{
	int	i;

	i = 0;
	while (i < g_settings.total)
	{
		pthread_mutex_destroy(&g_forks[i]);
		pthread_mutex_destroy(&g_settings.philos[i].eat_lock);
		i++;
	}
	pthread_mutex_destroy(&g_io_lock);
	pthread_mutex_destroy(&g_mainlock);
	free(g_forks);
	free(g_settings.philos);
}

int	main(int argc, char **argv)
{
	if ((argc < 5 || argc > 6) || !parse_args(argc++, argv, &g_settings))
	{
		printf("Arguments Error\n");
		return (1);
	}
	init();
	simulation(&g_settings);
	pthread_mutex_lock(&g_mainlock);
	destroy();
	return (0);
}
