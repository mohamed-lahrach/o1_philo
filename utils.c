/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [Your Name]                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: [Date]                                   #+#    #+#             */
/*   Updated: [Date]                                   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



/**
 * @brief Get the current timestamp in milliseconds.
 * 
 * @return long long Current time in milliseconds.
 */
long long   get_current_time(void)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}

/**
 * @brief Get the timestamp relative to the simulation start time.
 * 
 * @param start_time Simulation start time.
 * @return long long Timestamp relative to the start time.
 */
long long   get_timestamp(long long start_time)
{
    return (get_current_time() - start_time);
}

/**
 * @brief Print an action to the console in the required format.
 * 
 * @param philo Philosopher performing the action.
 * @param action Action string to print.
 */
void    print_action(t_philosopher *philo, char *action)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->someone_died){
        printf("%lld %d %s\n",get_timestamp(philo->data->start_time), philo->id, action);
        //printf("last_meal_time updated to %lld\n", philo->last_meal_time);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

/**
 * @brief Sleep for a given time in milliseconds, checking for death.
 * 
 * @param time_in_ms Time to sleep in milliseconds.
 * @param philo Philosopher sleeping.
 */
void    precise_usleep(long long time_in_ms, t_philosopher *philo)
{
    long long start_time;
    long long current_time;

    start_time = get_current_time();
    while (1)
    {
        current_time = get_current_time();
        if (current_time - start_time >= time_in_ms)
            break;
        usleep(100);
        pthread_mutex_lock(&philo->data->print_mutex);
        if (philo->data->someone_died)
        {
            pthread_mutex_unlock(&philo->data->print_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
}