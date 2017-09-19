/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_preci_and_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:52:26 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/18 23:09:22 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int do_preci_and_fill(t_fmt *fmt, t_buffer_static *sbuff, char *val, char sign)
{
	//printf("DEBUG | start do_precision_and_fillnbr\n");
	long long int nb;
	int ret;
	//(void)nbrlen;
	if (!fmt || !sbuff)
		return (0);
	ret = 0;
	nb = (!sign ? fmt->type.ll : fmt->type.ull);
	//printf("DEBUG 2 | middle check width | len:%d, precision:%d, width:%d\n",fmt->len, fmt->precision, fmt->width);
	if (fmt->precision > fmt->len)
	{
		//printf("passage\n");
		ret += do_filler_n(sbuff, "0", fmt->precision - fmt->len);
	}
	//printf("DEBUG 2-2 | add nbr\n");
	if (fmt->precision == 0 && nb == 0)
	{
		//printf("return; do preci and fillnbr\n");
		return (0);
	}
	/*if (nb < 10 && nb >= 0)
	{
		char test;
		test = (char)(nb + 48);
		return (do_filler(sbuff,  &test, 1) + ret);
	}
	else*/
		return (do_filler(sbuff, val, fmt->len) + ret);
		//return(fill_signed_number(sbuff, nb, multi, fmt) + ret);
}

int do_preci_and_fill_spec(t_fmt *fmt, t_buffer_static *sbuff, char *val)
{
	//printf("DEBUG | start do_precision_and_fillnbr\n");
	long long int nb;
	int ret;

	if (!fmt || !sbuff)
		return (0);
	ret = 0;
	nb = fmt->type.ull;
	if (fmt->precision > fmt->len)
		ret += do_filler_n(sbuff, "0", fmt->precision - fmt->len);
	//printf("DEBUG 2-2 | add nbr\n");
	if (fmt->precision == 0 && nb == 0)
		//return (fmt->flag_char[0] ? do_filler(sbuff, "0", 1) : 0);
		return (0);
	return (do_filler(sbuff, val, fmt->len) + ret);
}

int do_preci_and_fill_spec2(t_fmt *fmt, t_buffer_static *sbuff, char *val)
{
	//printf("DEBUG | start do_precision_and_fillnbr\n");
	long long int nb;
	int ret;
	//int len;
	
	if (!fmt || !sbuff)
		return (0);
	ret = 0;
	nb = fmt->type.ull;
	//printf("nbrlen:%d\tfmt->len:%d\n", nbrlen, fmt->len);
	//len = (nbrlen > fmt->len) ? nbrlen : fmt->len;
	if (fmt->precision > fmt->len)
	{
		//printf("DEBUG 2-1 | add nbr\n");
		ret += do_filler_n(sbuff, "0", fmt->precision - fmt->len);
	}
	//printf("DEBUG 2-2 | add nbr\n");
	if (fmt->precision == 0 && nb == 0)
	{
		//printf("DEBUG 2-3 | add nbr\n");
		return (fmt->flag_char[0] ? do_filler(sbuff, "0", 1) : 0);
	}
	//printf("DEBUG 2-4 | add nbr\n");
	return (do_filler(sbuff, val, fmt->len) + ret);
}