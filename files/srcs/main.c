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
		return (printf("Error: wrong usage\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error: malloc failed\n"), 1);
	if (data_parse(&data, argc, argv))
		return (free(data), printf("Error: wrong usage\n"), 1);
	if (data_init(&data))
		return (free(data), printf("Error: data initialization failed\n"), 1);
	if (data_destroy(&data))
		return (free(data), printf("Error: data destroy failed\n"), 1);
	return (0);
}
