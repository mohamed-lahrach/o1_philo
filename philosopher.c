#include "philo.h"

/**
 * @brief The routine executed by each philosopher thread.
 * 
 * @param arg Pointer to the philosopher structure.
 * @return void* NULL.
 */

void    *philosopher_routine(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    if (philo->id % 2 == 0)
        usleep(100);
    while (1)
    {
        take_forks(philo);
        eat(philo);
        put_down_forks(philo);
        if (philo->data->number_of_times_each_philosopher_must_eat != -1 &&
            philo->meals_eaten >= philo->data->number_of_times_each_philosopher_must_eat)
            break;
        philo_sleep(philo);
        think(philo);
        usleep(500);
        if(philo->data->someone_died)
            break;
    }
    return (NULL);
}