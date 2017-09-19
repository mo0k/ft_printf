/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:08:00 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/16 11:09:22 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void do_space(t_buffer_static *sbuff, int width, int *nbrlen, int *ret)
{
	//printf("DEBUG | 0 do_space\n");
	if (!sbuff || !nbrlen || !ret)
		return ;
	*ret += do_filler(sbuff, " ", 1);
	if (width > -1)// && fmt->precision == -1)
	{
		(*nbrlen)++;
		//printf("DEBUG 0-1 | nbrlen++\n");
	}
}