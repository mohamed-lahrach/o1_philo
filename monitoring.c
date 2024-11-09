/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:02:45 by mlahrach          #+#    #+#             */
/*   Updated: 2024/11/09 19:02:46 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philosophers_satisfied(t_philosopher *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (philos[i].meals_eaten < data->number_of_times_each_philosopher_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	monitor_philosophers(t_data *data)
{
	int i;
	long long time_since_last_meal;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->print_mutex);
			time_since_last_meal = get_current_time()
				- data->philos[i].last_meal_time;
			if (time_since_last_meal > data->time_to_die)
			{
				data->someone_died = 1;
				printf("%lld %d died\n", get_timestamp(data->start_time),
					data->philos[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				return ;
			}
			if (data->number_of_times_each_philosopher_must_eat != -1
				&& all_philosophers_satisfied(data->philos, data))
			{
				data->someone_died = 1;
				pthread_mutex_unlock(&data->print_mutex);
				return ;
			}
			pthread_mutex_unlock(&data->print_mutex);
			i++;
		}
		usleep(1000);
	}
}