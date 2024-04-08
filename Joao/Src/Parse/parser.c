/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:12:23 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/08 17:00:31 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parse.h"

static void	prep_nod_array(t_token **temp, t_parse *parse)
{
	int i;
	t_red *redir_temp;

	i = 0;
	while (*temp && (*temp)->type != PIPE)
	{
		while (*temp && (*temp)->type == DEFAULT)
		{
			parse->argv[i] = (*temp)->content;
			*temp = (*temp)->next;
			i++;
		}
		while (*temp && ((*temp)->type >= IN && (*temp)->type <= HEREDOC))
		{
			if ((*temp)->type == IN || (*temp)->type == HEREDOC)
			{
				redir_temp = ft_redir_new((*temp)->next->content, (*temp)->type);
				ft_add_redir(&parse->redir_in, redir_temp);
				(*temp) = (*temp)->next;
			}
			else if ((*temp)->type == OUT || (*temp)->type == APPEND)
			{
				redir_temp = ft_redir_new((*temp)->next->content, (*temp)->type);
				ft_add_redir(&parse->redir_out, redir_temp);
				(*temp) = (*temp)->next;
			}
		}
		if ((*temp))
			(*temp) = (*temp)->next;
	}
}

t_parse	*parse(t_token *token)
{
	t_parse	*parse;
	t_parse	*parse_temp;
	t_token	*token_pos;

	token_pos = token;
	parse = NULL;
	while (token)
	{
		parse_temp = ft_calloc(1, sizeof(t_token));
		parse_temp->argv = ft_calloc(ft_lstsize(token) + 1, sizeof(char **));
		prep_nod_array(&token, parse_temp);
		ft_add_redir((t_red **)&parse, (t_red *)parse_temp);
		if (token)
			token = token->next;
		// while (parse_temp->redir_in || parse_temp->redir_out)
		// {
		// 	if (parse_temp->redir_in)
		// 	{
		// 		printf("arg '%s' type in '%i' file in '%s' \n", *parse_temp->argv, parse_temp->redir_in->type, parse_temp->redir_in->filename);
		// 		parse_temp->redir_in = parse_temp->redir_in->next;
		// 	}
		// 	else if (parse_temp->redir_out)
		// 	{
		// 		printf("arg '%s' type out '%i' file out '%s' \n", *parse_temp->argv, parse_temp->redir_out->type, parse_temp->redir_out->filename);
		// 		// printf("file out %s \n", parse_temp->redir_out->filename);
		// 		parse_temp->redir_out = parse_temp->redir_out->next;
		// 	}
		// 	// parse->argv++;
		// }
	}
	token = token_pos;
	while (token)
	{
		token_pos = token->next;
		free(token->content);
		free(token);
		token = token_pos;
	}
	return (parse);
}
