/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [Your Name]                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: [Date]                                   #+#    #+#             */
/*   Updated: [Date]                                   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Philosopher takes the left and right forks (mutexes).
 *
 * @param philo Philosopher taking the forks.
 */
void take_forks(t_philosopher *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_action(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_action(philo, "has taken a fork");
}

/**
 * @brief Philosopher eats for time_to_eat milliseconds.
 *
 * @param philo Philosopher eating.
 */
void eat(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->data->print_mutex);
    print_action(philo, "is eating");
    precise_usleep(philo->data->time_to_eat, philo);
    philo->meals_eaten += 1;
}

/**
 * @brief Philosopher puts down the forks (mutexes).
 *
 * @param philo Philosopher putting down the forks.
 */
void put_down_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

/**
 * @brief Philosopher sleeps for time_to_sleep milliseconds.
 *
 * @param philo Philosopher sleeping.
 */
void philo_sleep(t_philosopher *philo)
{
    print_action(philo, "is sleeping");
    precise_usleep(philo->data->time_to_sleep, philo);
}

/**
 * @brief Philosopher thinks.
 *
 * @param philo Philosopher thinking.
 */
void think(t_philosopher *philo)
{
    print_action(philo, "is thinking");
}

