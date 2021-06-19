/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <abkssiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:25:33 by abkssiba          #+#    #+#             */
/*   Updated: 2021/06/19 16:10:32 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if ((argc < 5 || argc > 6) || !parse_args(argc++, argv, &g_settings))
	{
		printf("Arguments Error\n");
		return (1);
	}
	g_eat_count = 0;
	pthread_mutex_init(&g_io_lock, NULL);
	g_forks = malloc(g_settings.total * sizeof(pthread_mutex_t));
	g_settings.phlios = malloc(g_settings.total * sizeof(t_philo));
	simulation(&g_settings);
	free(g_forks);
	free(g_settings.phlios);
	return (0);
}
