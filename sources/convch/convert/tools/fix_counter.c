/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:53:32 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/18 17:03:15 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int fix_count_signed(t_fmt *fmt, int nbrlen)
{
	//printf("DEBUG | start fix_counter\n");
	if (!fmt)
		return (0);
	if (fmt->precision > fmt->len)
	{
		//printf("choix 1\n");
		//sleep(10);
		return ((nbrlen > fmt->len ||
			(fmt->type.ll >= 0 && fmt->flag_char[3]) ||
			fmt->type.ll < 0) ? fmt->precision + 1 : fmt->precision);
	}
	else
	{
		//printf("DEBUG 2-4 | \n");
		//sleep(10);
		if (((fmt->type.ll >= 0 && fmt->flag_char[3]) ||
			fmt->type.ll < 0))
			return (fmt->len + 1);
		else if (fmt->precision == 0 && fmt->type.ll == 0)
			return (0);
		else
			return (nbrlen);
	}
}
int fix_count_unsigned(t_fmt *fmt, int nbrlen)
{
	//printf("DEBUG | start fix_counter\n");
	if (!fmt)
		return (0);
	if (fmt->precision > fmt->len)
	{
		//printf("choix 1\n");
		//sleep(10);
		return ((nbrlen > fmt->len || fmt->flag_char[3]) ?
										fmt->precision + 1 : fmt->precision);
	}
	else
	{
		//printf("DEBUG 2-4 | \n");
		//sleep(2);
		if (fmt->flag_char[3])
			return (fmt->len + 1);
		else if (fmt->precision == 0 && fmt->type.ull == 0)
			return (0);
		else
			return (nbrlen);
	}
}

int fix_count_unsigned1(t_fmt *fmt, int nbrlen, char *ptr)
{
	//printf("DEBUG | start fix_counter\n");
	if (!fmt)
		return (0);
	if (fmt->precision > fmt->len)
	{
		//printf("choix 1 => precision:%d,nbrlen:%d, fmt->len:%d, fmt->flag_char[0]:%d\n", fmt->precision, nbrlen, fmt->len, fmt->flag_char[0]);
		//sleep(10);
		if ((nbrlen > fmt->len || fmt->flag_char[3]) && (fmt->flag_char[0] && ptr && *ptr != '0'))
			return (fmt->precision + 2);
		return (nbrlen > fmt->len || fmt->flag_char[3] ?
										fmt->precision + 1 : fmt->precision);
	}
	else
	{
		//printf("DEBUG 2-4 | \n");
		//sleep(2);
		if (fmt->flag_char[3])
			return (fmt->len + 1);
		else if (fmt->precision == 0 && fmt->type.ull == 0)
			return (0);
		else
			return (nbrlen);
	}
}