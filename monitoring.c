/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [Your Name]                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: [Date]                                   #+#    #+#             */
/*   Updated: [Date]                                   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Check if all philosophers have eaten the required number of times.
 * 
 * @param philos Array of philosophers.
 * @param data Shared data structure.
 * @return int 1 if all have eaten enough, 0 otherwise.
 */
int all_philosophers_satisfied(t_philosopher *philos, t_data *data)
{
    int i = 0;

    while (i < data->number_of_philosophers)
    {
        if (philos[i].meals_eaten < data->number_of_times_each_philosopher_must_eat)
            return (0);
        i++;
    }
    return (1);
}

/**
 * @brief Monitor philosophers to detect if any has died or if simulation should end.
 * 
 * @param philos Array of philosophers.
 * @param data Shared data structure.
 */
void    monitor_philosophers(t_philosopher *philos, t_data *data)
{
    int         i;
    long long   time_since_last_meal;

    while (1)
    {
        i = 0;
        while (i < data->number_of_philosophers)
        {
            pthread_mutex_lock(&data->print_mutex);
            time_since_last_meal = get_current_time() - philos[i].last_meal_time;
            if (time_since_last_meal >= data->time_to_die)
            {
                data->someone_died = 1;
                printf("%lld %d died\n",
                    get_timestamp(data->start_time), philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);
                return ;
            }
            if (data->number_of_times_each_philosopher_must_eat != -1 &&
                all_philosophers_satisfied(philos, data))
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