/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:28:49 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/18 23:09:48 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void add_zero(char **ptr, int *len)
{
	if (**ptr == '0')
		return ;
	--*ptr;
	**ptr = '0';
	++*len;
}

void convert_octal(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret)
{
	int nbrlen;
	char test[65];
	char *ptr;
	int diff;

	if (!(ptr = init_var_unsigned(fmt, args, test, 8)))
		return ;
	if (fmt->flag_char[0])
		add_zero(&ptr, &fmt->len);
	/*{
		--ptr;
		*ptr = '0';
		++fmt->len;
	}*/
	nbrlen = fmt->len;
	if (fmt->flag_char[4])
		do_space(sbuff, fmt->width, &nbrlen, ret);
	if (fmt->precision == -1 && fmt->width == -1)
	{
		*ret += do_filler(sbuff, ptr, fmt->len);
		return ;//(more_speed1(fmt, sbuff, ptr, ret));
	}
	if (fmt->flag_char[2])
		*ret = do_preci_and_fill_spec2(fmt, sbuff, ptr);
	if (fmt->width > fmt->precision)
		if ((diff = fmt->width - fix_count_unsigned1(fmt, nbrlen, ptr)) >= 0)
			*ret += (fmt->flag_char[1] && fmt->precision == -1) ?
											do_filler_n(sbuff, "0", diff) :
											do_filler_n(sbuff, " ", diff);
	if (!fmt->flag_char[2])
		*ret = do_preci_and_fill_spec2(fmt, sbuff, ptr);
}
