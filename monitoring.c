/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:02:45 by mlahrach          #+#    #+#             */
/*   Updated: 2024/11/11 22:11:21 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philosophers_satisfied(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->philos->meals_eaten < data->nbr_times_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	check_philosopher(t_data *data, int i)
{
	long long	time_since_last_meal;
	long		current_time;

	pthread_mutex_lock(&data->print_mutex);
	current_time = get_current_time(MILLISECONDS);
	time_since_last_meal = current_time - data->philos[i].time_last_meal;
	if (time_since_last_meal > data->time_to_die)
	{
		data->dead_or_full_eaten = 1;
		printf("%lld %d died\n", get_timestamp(data->start_time),
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	if (data->nbr_times_must_eat != -1 && all_philosophers_satisfied(data))
	{
		data->dead_or_full_eaten = 1;
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->print_mutex);
}

void	monitor_philosophers(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			check_philosopher(data, i);
			if (data->dead_or_full_eaten)
				return ;
			i++;
		}
		usleep(1000);
	}
}
