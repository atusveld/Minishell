/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:12:23 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/05 13:10:00 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parse.h"

static void	prep_nod_array(t_token *temp, t_parse *parse)
{
	int i;

	i = 0;
	while (temp)
	{
		while (temp && temp->type == DEFAULT)
		{
			parse->argv[i] = temp->content;
			temp = temp->next;
			i++;
		}
		while (temp && (temp->type >= IN && temp->type <= HEREDOC))
		{
			if (temp->type == IN || temp->type == HEREDOC)
			{
				parse->redir_in->type = temp->type;
				parse->redir_in->filename = temp->next->content;
				temp = temp->next;
			}
			else if (temp->type == OUT || temp->type == APPEND)
			{
				parse->redir_out->type = temp->type;
				parse->redir_out->filename = temp->next->content;
				temp = temp->next;
			}
		}
		if (temp)
			temp = temp->next;
	}
}

int	parse(t_token *token)
{
	// (void)token;
	t_parse	*parse;
	t_red	*redir_in;
	t_red	*redir_out;
	
	redir_in = ft_calloc(1, sizeof(t_red));
	redir_out = ft_calloc(1, sizeof(t_red));
	parse = ft_calloc(1, sizeof(t_token));
	parse->argv = ft_calloc(ft_lstsize(token) + 1, sizeof(char **));
	prep_nod_array(token, parse);
	while (*parse->argv && (parse->redir_in || parse->redir_out))
	{
		printf("%s ", *parse->argv);
		printf("%s ", parse->redir_in->filename);
		printf("%s ", parse->redir_out->filename);
		parse->argv++;
	}
	printf("\n");
	return (0);
}
