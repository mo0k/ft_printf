/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:35:29 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/25 22:51:03 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void			convert_wchar(t_fmt *fmt, t_buffer_static *sbuff,
														va_list *args, int *ret)
{
	unsigned char	c[5];

	fmt->type.wchar = va_arg(*args, wchar_t);
	if (fmt->type.wchar < 0)
		return (ret_error(ret));
	fmt->len = 1;
	if (!init_wchar(c, fmt->type.wchar, &fmt->len))
		return (ret_error(ret));
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
