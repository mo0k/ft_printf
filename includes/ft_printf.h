/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 08:50:33 by mo0ky             #+#    #+#             */
/*   Updated: 2017/08/05 22:59:38 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>
#include <libft.h>

#define FLAG_CHAR "#0-+ "
#define FLAG_CONVERT "sSpdDioOuUxXcC"

enum e_flag_len
{
	FLAG_LEN_NODEF,
	FLAG_LEN_HH,
	FLAG_LEN_H,
	FLAG_LEN_LL,
	FLAG_LEN_L,
	FLAG_LEN_J,
	FLAG_LEN_Z
};

typedef struct			s_flag_char
{
	char				key[5];
	int					flag[5];
}						t_flag_char;

typedef struct			s_format
{
	int					fieldwidth;
	int					precison;
	t_flag_char			flag_char;
	enum e_flag_len		flag_len;
	char				flag_convert;
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