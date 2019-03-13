/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:48:49 by dfonarev          #+#    #+#             */
/*   Updated: 2019/02/22 17:48:52 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt_floor(int x)
{
	int	start;
	int	end;
	int	mid;
	int	ans;

	start = 0;
	end = x / 2;
	mid = 0;
	ans = 0;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (mid * mid == x)
			return (mid);
		else if (mid * mid < x)
		{
			start = mid + 1;
			ans = mid;
		}
		else if (mid * mid > x)
			end = mid - 1;
	}
	return (ans);
}
