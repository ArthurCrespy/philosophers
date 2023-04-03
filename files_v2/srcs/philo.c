/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:53:45 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/25 13:53:48 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_data  data;

	philo = (t_philo *)arg;
	data = *(t_data *)philo->data;
	while (philo->(*data)->philo_nb != philo->data->philo_alive)
		;
	printf("Philosopher %d is alive\n", philo->id);
	return (NULL);
}