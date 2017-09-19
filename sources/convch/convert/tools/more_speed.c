/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_speed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:24:40 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/16 11:31:05 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void more_speed_signed(t_fmt *fmt, t_buffer_static *sbuff, char *val, int *ret)
{
	//printf("start more_speed\n");
	long long int nb;

	nb = fmt->type.ll;
	do_sign(fmt, sbuff, nb, ret);
	/*if (nb < 10 && nb >= 0)
	{
		char test;
		test = (char)(nb + 48);
		ret += do_filler(sbuff,  &test, 1);
	}
	else*/
		//*ret += fill_signed_number(sbuff, nb, multi, fmt);
		*ret += do_filler(sbuff, val, fmt->len);
	return;
}

void more_speed_unsigned(t_fmt *fmt, t_buffer_static *sbuff, char *val, int *ret)
{
	//printf("start more_speed\n");
	//long long int nb;

	//nb = fmt->type.ll;
	//do_sign(fmt, sbuff, nb, ret);
	/*if (nb < 10 && nb >= 0)
	{
		char test;
		test = (char)(nb + 48);
		ret += do_filler(sbuff,  &test, 1);
	}
	else*/
		//*ret += fill_signed_number(sbuff, nb, multi, fmt);
		*ret += do_filler(sbuff, val, fmt->len);
	return;
}
