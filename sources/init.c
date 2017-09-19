/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 00:06:02 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/17 00:29:15 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		init(t_print *print, const char *format)
{
	if (!print || !format)
		return (0);
	init_buffer_static(&print->sbuff);
	//init_buffer_malloc(&print->mbuff);
	//init_format(&print->format_flag);
	//print->args = 0;
	print->format = format;
	print->ret = 0;
	print->convfunc[0] = &convert_str;
	print->convfunc[1] = &convert_wstr;//S => (t_wchar*)
	print->convfunc[2] = 0;//p => (void*)
	print->convfunc[3] = &convert_int;
	print->convfunc[4] = &convert_int;
	print->convfunc[5] = &convert_int;
	print->convfunc[6] = &convert_octal;
	print->convfunc[7] = &convert_octal;
	print->convfunc[8] = &convert_uint;
	print->convfunc[9] = &convert_uint;
	print->convfunc[10] = &convert_hexa;
	print->convfunc[11] = &convert_hexa;
	print->convfunc[12] = &convert_char;
	print->convfunc[13] = &convert_wchar;//C => (t_wchar)
	print->convfunc[14] = &noconvert;
	print->convfunc[15] = 0;
	return (1);
}