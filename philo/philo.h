/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <abkssiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:29:19 by abkssiba          #+#    #+#             */
/*   Updated: 2021/06/30 16:11:26 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	pthread_t		th;
	pthread_t		th_check;
	int				left;
	int				right;
	unsigned int	limit;
	int				eat_count;
	pthread_mutex_t	eat_lock;
}				t_philo;

typedef struct s_settings
{
	int		total;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nbt_eat;
	int		i;
	t_philo	*philos;
}	t_settings;

pthread_mutex_t	g_io_lock;
unsigned int	g_start_time;
int				g_eat_count;
pthread_mutex_t	*g_forks;
t_settings		g_settings;
pthread_mutex_t	g_mainlock;

/* simulation */
int				simulation(t_settings *settings);

/* parser */
int				parse_args(int argc, char **argv, t_settings *settings);

/* print */
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);

/* utils */
unsigned int	get_time(void);
void			print_stat(int stat, int id);
void			eat_count(t_philo *philo);

#endif