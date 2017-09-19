/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 20:45:58 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/19 18:18:39 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <wchars.h>	

static void		do_precision_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	if (fmt->precision <= fmt->len)
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, fmt->precision);
	else
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, fmt->len);
}

static void		do_width_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	char flag_minus;
	char flag_zero;
	int count;

	flag_zero = fmt->flag_char[1];
	flag_minus = fmt->flag_char[2];
	if (flag_minus)
	{
		//printf("test:%d\n", fmt->len);
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, fmt->len);
		//printf("ret:%d\n", *ret);
	}
	count = fmt->len;
	if (count < fmt->width)
	{
		//printf("add largeur\n");
		if (flag_zero)
			*ret += do_filler_n(sbuff, "0", fmt->width - fmt->len);
		else
			*ret += do_filler_n(sbuff, " ", fmt->width - fmt->len);
		count++;
	}
	if (!flag_minus)
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, fmt->len);
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
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, test);
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
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, test);
	}
}

void convert_wstr(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret)
{
	static wchar_t null[] = L"(null)";

	fmt->type.wstr = va_arg(*args, wchar_t*);
	if (!fmt->type.wstr)
		fmt->type.wstr = null;
	fmt->len = ft_wstrlen(fmt->type.wstr);
	//printf("fmt->len:%d\n", fmt->len);
	if (fmt->width == -1 && fmt->precision == -1)
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, fmt->len);
	else if (fmt->width > -1 && fmt->precision > -1)
		do_full_convert(fmt, sbuff, ret);
	else if (fmt->width > -1 && fmt->precision == -1)
		do_width_convert(fmt, sbuff, ret);
	else
		do_precision_convert(fmt, sbuff, ret);
	//printf("convert_wstr ret:%d, size:%zu\n", *ret, sbuff->used_size);
}