/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:03:09 by mlahrach          #+#    #+#             */
/*   Updated: 2024/11/09 19:03:10 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}

long long	get_timestamp(long long start_time)
{
	return (get_current_time() - start_time);
}

void	print_action(t_philosopher *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_died)
	{
		printf("%lld %d %s\n", get_timestamp(philo->data->start_time),
			philo->id, action);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
void	precise_usleep(long long time_in_ms, t_philosopher *philo)
{
	long long	start_time;
	long long	current_time;

	start_time = get_current_time();
	while (1)
	{
		current_time = get_current_time();
		if (current_time - start_time >= time_in_ms)
			break ;
		usleep(100);
		pthread_mutex_lock(&philo->data->print_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}
// int simulation_finished(t_data *data)
// {
//     if (data->someone_died)
//         return (1);
//     if (data->number_of_times_each_philosopher_must_eat != -1)
//     {
//         if (all_philosophers_satisfied(data->, data))
//             return (1);
//     }
//     return (0);
// }

// void precise_usleep(long msec, t_data *data)
// {
//     long start;
//     long elapsed;
//     long rem;

//     start = get_current_time() * 1000;
//     while ((get_current_time() * 1000) - start < msec)
//     {
//         // 1
//         if (simulation_finished(data))
//             break ;
//         elapsed = (get_current_time() * 1000) - start;
//         rem = msec - elapsed;
//         if (rem > 1000)
//             usleep(rem / 2);
//         else
//         {
//             // spinlocker
//             while ((get_current_time() * 1000) - start < msec)
//                 ;
//         }
//     }
// }