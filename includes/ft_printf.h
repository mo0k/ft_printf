/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 08:50:33 by mo0ky             #+#    #+#             */
/*   Updated: 2017/08/11 23:52:38 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>
#include <libft.h>

#define FLAG_CHAR "#0-+ "
#define FLAG_CONVERT "sSpdDioOuUxXcC"

enum e_flag_mlen
{
	FLAG_MLEN_NODEF,
	FLAG_MLEN_HH,
	FLAG_MLEN_H,
	FLAG_MLEN_LL,
	FLAG_MLEN_L,
	FLAG_MLEN_J,
	FLAG_MLEN_Z
};

typedef struct			s_flag_char
{
	char				key[5];
	int					flag[5];
}						t_flag_char;

typedef struct			s_format
{
	int					fieldwidth;
	int					precision;
	t_flag_char			flag_char;
	enum e_flag_mlen	flag_mlen;
	//char				mlen[3];
	char				convch;
}						t_format;

typedef struct			s_print
{
	t_buffer_static		sbuff;
	t_buffer_malloc		mbuff;
	va_list				*args;
	const char 			*format;
	int					ret;
}						t_print;

int		ft_printf(const char *format, ...);
int		init(t_print *print, const char *format);
int		do_format(char *format_string, t_buffer_malloc *mbuff, va_list *args);

#endif