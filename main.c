#include "philo.h"

/**
 * @brief Clean up resources by destroying mutexes and freeing memory.
 *
 * @param data Shared data structure.
 * @param philos Array of philosophers.
 */
void clean_up(t_data *data, t_philosopher *philos)
{
    int i = 0;

    pthread_mutex_destroy(&data->print_mutex);
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    free(data->forks);
    free(philos);
}


/**
 * @brief Main function to initialize data, create threads, and start simulation.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */

int main(int argc, char **argv)
{
    t_data data;
    t_philosopher *philos;
    int i = 0;

    ft_memset(&data, 0, sizeof(t_data));
    parse_arguments(argc, argv, &data);
    data.start_time = get_current_time();

    if (initialize_philosophers(&data, &philos))
        return (1);
    while (i < data.number_of_philosophers)
    {
        pthread_create(&philos[i].thread, NULL, philosopher_routine, &philos[i]);
        i++;
    }
    monitor_philosophers(philos, &data);
    i = 0;
    while (i < data.number_of_philosophers)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    clean_up(&data, philos);
    return (0);
}
