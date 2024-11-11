/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:03:09 by mlahrach          #+#    #+#             */
/*   Updated: 2024/11/11 18:52:01 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(enum e_units unit)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (unit == MILLISECONDS)
		return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
	else if (unit == MICROSECONDS)
		return ((time.tv_sec * 1000000LL) + time.tv_usec);
	return (0);
}

long long	get_timestamp(long long start_time)
{
	return (get_current_time(MILLISECONDS) - start_time);
}

void	print_action(t_philosopher *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->dead_or_full_eaten)
	{
		printf("%lld %d %s\n", get_timestamp(philo->data->start_time),
			philo->id, action);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	precise_usleep(long long msec, t_philosopher *philo)
{
	long	start;
	long	elapsed;
	long	rem;

	msec = msec * 1000;
	start = get_current_time(MICROSECONDS);
	while (get_current_time(MICROSECONDS) - start < msec)
	{
		if (philo->data->dead_or_full_eaten)
			break ;
		elapsed = get_current_time(MICROSECONDS) - start;
		rem = msec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (get_current_time(MICROSECONDS) - start < msec)
				;
		}
	}
}
