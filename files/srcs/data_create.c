/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:01:26 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/22 17:01:26 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void create_node(t_data **data, int id)
{
	t_philo *tmp;
	t_philo *new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return ;
	new->id = id;
	new->fork_avail = 0;
	new->eat_last = 0;
	new->eat_count = 0;
	if (!(*data)->philo)
	{
		new->next = new;
		(*data)->philo = new;
	}
	else
	{
		tmp = (*data)->philo;
		while (tmp->next != (*data)->philo)
			tmp = tmp->next;
		tmp->next = new;
		new->next = (*data)->philo;
	}
}

void create_table(t_data **data)
{
	int id;

	id = 0;
	(*data)->all_alive = 0;
	(*data)->philo = NULL;
	(*data)->data_access = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	id = (*data)->nb_philo;
	while (id != 0)
	{
		create_node(&(*data), id);
		id--;
	}
	ft_goto_philo(&(*data), (*data)->nb_philo);
	id = (*data)->nb_philo;
	while (id != 0)
	{
		(*data)->id_tmp = id;
		//(*data)->philo->data = *data;
		pthread_create(&(*data)->philo->thread, NULL, philosopher, (void*)(*data));
		(*data)->philo = (*data)->philo->next;
		//pthread_mutex_init(&(*data)->philo->fork_mutex, NULL);
		usleep(10000);
		id--;
	}
	id = 0;
	gettimeofday(&(*data)->time_start, NULL);
	(*data)->all_alive = 1;
	while (id != (*data)->nb_philo)
	{
		pthread_join((*data)->philo->thread, NULL);
		(*data)->philo = (*data)->philo->next;
		id++;
	}
}