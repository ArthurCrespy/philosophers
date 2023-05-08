/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:12:40 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/05 12:56:59 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	data_parse(t_data **data, int argc, char **argv)
{
	(*data)->philo_nb = ft_atoi(argv[1]);
	if ((*data)->philo_nb <= 0)
		return (1);
	(*data)->time_to_die = ft_atoi(argv[2]);
	if ((*data)->time_to_die <= 0)
		return (1);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	if ((*data)->time_to_eat <= 0)
		return (1);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if ((*data)->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
		(*data)->eat_nb = ft_atoi(argv[5]);
	else
		(*data)->eat_nb = -1;
	return (0);
}
