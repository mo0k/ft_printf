/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prefix_hexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 00:30:11 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/25 00:31:12 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		add_prefix_hexa(t_buffer_static *sbuff, char convch, int *len)
{
	char	c[2];

	*len += 2;
	c[0] = '0';
	c[1] = (convch == 'p') ? 'x' : convch;
	return (do_filler(sbuff, c, 2));
}
