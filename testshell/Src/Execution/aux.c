/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aux.c                      	                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
 
 #include "../../Includes/alex.h"

 char	*ft_strjoin_three(char *s1, char *s2, char *s3)
 {
	char	*temp;
	char	*str;

	temp = ft_strjoin(s1, s2);
	str = ft_strjoin(temp, s3);
	free (temp);
	return (str);
 }