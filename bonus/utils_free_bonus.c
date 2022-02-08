/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:49:54 by hakim             #+#    #+#             */
/*   Updated: 2022/02/09 03:45:05 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	error(int mode)
{
	if (mode == OPEN_ERR)
		ft_putstr_fd("Error: Initial file opening failed\n", 2);
	if (mode == MALLOC_ERR)
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
	exit(EXIT_FAILURE);
}

void	*ft_free_int(int *arr)
{
	free(arr);
	arr = 0;
	return (0);
}

void	*ft_free_str(char *str)
{
	free(str);
	str = 0;
	return (0);
}

void	*ft_free_splitted(char **splitted)
{
	int	index;

	index = 0;
	while (splitted[index] != 0)
		ft_free_str(splitted[index++]);
	free(splitted);
	splitted = 0;
	return (0);
}
