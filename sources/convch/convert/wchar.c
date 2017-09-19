/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:35:29 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/19 18:03:26 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void convert_wchar(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret)
{
	//printf("DEBUG convert_wchar\n");
	//(void)args;
	//unsigned int e;
	unsigned char c[5];

	fmt->type.wchar = va_arg(*args, wchar_t);
	if (fmt->type.wchar < 0)
	{
		*ret = -1;
		//printf("par la ret -1\n");
		return ;
	}
	//fmt->len = fmt->type.wchar ? 1 : 0;
	fmt->len = 1;
	if (!init_wchar(c, fmt->type.wchar, &fmt->len))
	{
		*ret = -1;
		return;
	}
	if (fmt->width > -1)
	{
		if (fmt->flag_char[2])
			ret += do_filler(sbuff, c, fmt->len);
		if (fmt->len < fmt->width)
			ret += fmt->flag_char[1] ?
				do_filler_n(sbuff, "0", fmt->width - fmt->len) :
				do_filler_n(sbuff, " ", fmt->width - fmt->len);
		if (!fmt->flag_char[2])
			ret += do_filler(sbuff, c, fmt->len);
	}
	else
		ret += do_filler(sbuff, c, fmt->len);
}