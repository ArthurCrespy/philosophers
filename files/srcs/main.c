/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:50:45 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/14 17:41:32 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (args_check(argc, argv))
		return (printf("Error: args_check failed\n"), 1);
	data = malloc(sizeof(t_data));
	if (data_parse(&data, argc, argv))
		return (printf("Error: data_parse failed\n"), 1);
	if (data_init(&data))
		return (printf("Error: data_init failed\n"), 1);
	if (data_destroy(&data))
		return (printf("Error: data_destroy failed\n"), 1);
	return (0);
}
