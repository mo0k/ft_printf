/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 20:45:58 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/19 18:19:03 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		do_precision_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	if (fmt->precision <= fmt->len)
		*ret += do_filler(sbuff, fmt->type.s, fmt->precision);
	else
		*ret += do_filler(sbuff, fmt->type.s, fmt->len);
}

static void		do_width_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	char flag_minus;
	char flag_zero;
	int count;

	flag_zero = fmt->flag_char[1];
	flag_minus = fmt->flag_char[2];
	if (flag_minus)
		*ret += do_filler(sbuff, fmt->type.s, fmt->len);
	count = fmt->len;
	if (count < fmt->width)
	{
		if (flag_zero)
			*ret += do_filler_n(sbuff, "0", fmt->width - fmt->len);
		else
			*ret += do_filler_n(sbuff, " ", fmt->width - fmt->len);
		count++;
	}
	if (!flag_minus)
		*ret += do_filler(sbuff, fmt->type.s, fmt->len);
}
static void		do_full_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	char flag_minus;
	char flag_zero;

	flag_zero = fmt->flag_char[1];
	flag_minus = fmt->flag_char[2];
	if (flag_minus)
	{
		int test = (fmt->precision < fmt->len) ? fmt->precision : fmt->len;
		*ret += do_filler(sbuff, fmt->type.s, test);
	}
	if (fmt->precision <= fmt->len)
	{
		if (fmt->precision < fmt->width)
		{
			if (flag_zero)
				*ret += do_filler_n(sbuff, "0", fmt->width - fmt->precision);
			else
				*ret += do_filler_n(sbuff, " ", fmt->width - fmt->precision);
		}
	}
	else if (fmt->len < fmt->width)
	{
		if (flag_zero)
			*ret += do_filler_n(sbuff, "0", fmt->width - fmt->len);
		else
			*ret += do_filler_n(sbuff, " ", fmt->width - fmt->len);
	}
	if (!flag_minus)
	{
		int test = (fmt->precision < fmt->len) ? fmt->precision : fmt->len;
		*ret += do_filler(sbuff, fmt->type.s, test);
	}
}

void convert_str(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret)
{
	static char null[] = "(null)";
	if (!(fmt->type.s = va_arg(*args, char*)))
	//{
		//char null[7];
		//ft_strcpy(null, "(null)");
		fmt->type.s = null;
	//}
	fmt->len = ft_strlen(fmt->type.s);
	if (fmt->width == -1 && fmt->precision == -1)
		*ret += do_filler(sbuff, fmt->type.s, fmt->len);
	else if (fmt->width > -1 && fmt->precision > -1)
		do_full_convert(fmt, sbuff, ret);
	else if (fmt->width > -1 && fmt->precision == -1)
		do_width_convert(fmt, sbuff, ret);
	else
		do_precision_convert(fmt, sbuff, ret);
}