/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 20:45:58 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 21:36:27 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <wchars.h>

static void		do_precision_convert(t_fmt *fmt, t_buffer_static *sbuff, \
																	int *ret)
{
	if (fmt->precision == 0)
		return ;
	if (fmt->precision <= fmt->len)
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, fmt->precision);
	else
		*ret += do_filler_wstr(sbuff, fmt->type.wstr, fmt->len);
}

static void		do_width_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	int				tmp;

	if (fmt->flag_char[2])
	{
		if ((tmp = do_filler_wstr(sbuff, fmt->type.wstr, fmt->len)) == -1)
			return (ret_error(ret));
		*ret += tmp;
	}
	if (fmt->len < fmt->width)
		*ret += (fmt->flag_char[1]) ?
						do_filler_n(sbuff, "0", fmt->width - fmt->len) :
						do_filler_n(sbuff, " ", fmt->width - fmt->len);
	if (!fmt->flag_char[2])
	{
		if ((tmp = do_filler_wstr(sbuff, fmt->type.wstr, fmt->len)) == -1)
			return (ret_error(ret));
		*ret += tmp;
	}
}

static void		do_width(t_fmt *fmt, t_buffer_static *sbuff, int *ret, int len)
{
	*ret += (fmt->flag_char[1]) ?
						do_filler_n(sbuff, "0", len) :
						do_filler_n(sbuff, " ", len);
}

static void		do_full_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	int				len;
	int				tmp;

	len = 0;
	if (fmt->flag_char[2])
	{
		tmp = (fmt->precision < fmt->len) ? fmt->precision : fmt->len;
		if (tmp && (len = do_filler_wstr(sbuff, fmt->type.wstr, tmp)) == -1)
			return (ret_error(ret));
		*ret += len;
	}
	if (fmt->precision <= fmt->len)
	{
		if (fmt->precision < fmt->width)
			do_width(fmt, sbuff, ret, fmt->width - fmt->precision);
	}
	else if (fmt->len < fmt->width)
		do_width(fmt, sbuff, ret, fmt->width - fmt->len);
	if (!fmt->flag_char[2])
	{
		tmp = (fmt->precision < fmt->len) ? fmt->precision : fmt->len;
		if (tmp && (len = do_filler_wstr(sbuff, fmt->type.wstr, tmp)) == -1)
			return (ret_error(ret));
		*ret += len;
	}
}

void			convert_wstr(t_fmt *f, t_buffer_static *sbuff, \
														va_list *args, int *ret)
{
	static wchar_t	null[] = L"(null)";
	int				tmp;

	f->type.wstr = va_arg(*args, wchar_t*);
	if (!f->type.wstr)
		f->type.wstr = null;
	f->len = (f->precision < 1) ? ft_wstrlen(f->type.wstr) :
								ft_wstrnlen(f->type.wstr, f->precision);
	if (f->len < 0 && (f->precision == -1 || f->precision > f->len * -1))
		return (ret_error(ret));
	else if (f->len < 0)
		f->len *= -1;
	if (f->width == -1 && f->precision == -1)
	{
		if ((tmp = do_filler_wstr(sbuff, f->type.wstr, f->len)) == -1)
			return (ret_error(ret));
		*ret += tmp;
	}
	else if (f->width > -1 && f->precision > -1)
		do_full_convert(f, sbuff, ret);
	else if (f->width > -1 && f->precision == -1)
		do_width_convert(f, sbuff, ret);
	else
		do_precision_convert(f, sbuff, ret);
}
