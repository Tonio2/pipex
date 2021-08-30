/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:34:27 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 22:11:02 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	len;
	int	cpt;

	cpt = -1;
	len = ft_strlen(s);
	while (++cpt <= len)
		if (*(s + cpt) == c)
			return ((char *)(s + cpt));
	return (0);
}
