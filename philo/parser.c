/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <abkssiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:42:56 by abkssiba          #+#    #+#             */
/*   Updated: 2021/06/18 17:20:41 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_stringisnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		iss;
	long	value;
	long	number;
	int		sign;

	iss = 0;
	number = 0;
	sign = 1;
	while ((str[iss] == ' ' || (str[iss] >= '\t' && str[iss] <= '\r'))
		&& str[iss] != '\0')
		iss++;
	if (str[iss] == '-' || str[iss] == '+')
		if (str[iss++] == '-')
			sign = -1;
	while (ft_isdigit(str[iss]))
	{
		value = number;
		number = (number * 10) + (sign * (str[iss++] - '0'));
		if (sign == 1 && value > number)
			return (-1);
		else if (sign == -1 && value < number)
			return (0);
	}
	return (number);
}

int	check_valid(int i, int res)
{
	if (i == 5 && res < 0)
		return (0);
	else if (i == 1 && (res < 0 || res > 200))
		return (0);
	else if (i > 1 && i < 5 && res < 60)
		return (0);
	return (1);
}

int	parse_args(int argc, char **argv, t_settings *settings)
{
	int	i;
	int	res;

	i = 0;
	settings->nbt_eat = -1;
	while (argv[++i])
	{
		if (!ft_stringisnumber(argv[i]))
			return (0);
		res = ft_atoi(argv[i]);
		if (i == 1)
			settings->total = res;
		else if (i == 2)
			settings->t_die = res;
		else if (i == 3)
			settings->t_eat = res;
		else if (i == 4)
			settings->t_sleep = res;
		else
			settings->nbt_eat = res;
		if (!check_valid(i, res))
			return (0);
	}
	return (1);
}
