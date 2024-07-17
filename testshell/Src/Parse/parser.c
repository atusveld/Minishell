/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:12:23 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/09 11:35:42 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	add_redir(t_token **temp, t_parse *parse, t_red *redir_temp)
{
	char *filename;

	filename = ft_strdup((*temp)->next->content);
	if ((*temp)->type == IN)
	{
		redir_temp = ft_redir_new(filename, (*temp)->type);
		ft_add_redir(&parse->redir_in, redir_temp);
		(*temp) = (*temp)->next;
	}
	else if ((*temp)->type == OUT || (*temp)->type == APPEND)
	{
		redir_temp = ft_redir_new(filename, (*temp)->type);
		ft_add_redir(&parse->redir_out, redir_temp);
		(*temp) = (*temp)->next;
	}
}

// static void	out_redir(t_token **temp, t_parse *parse, t_red *redir_temp)
// {
// 	if ((*temp)->type == OUT || (*temp)->type == APPEND)
// 	{
// 		redir_temp = ft_redir_new((*temp)->next->content, (*temp)->type);
// 		ft_add_redir(&parse->redir_out, redir_temp);
// 		(*temp) = (*temp)->next;
// 	}
// }

static void	prep_nod_array(t_token **token, t_parse *parse, t_env *env)
{
	int		i;
	t_red	*redir_temp;

	redir_temp = NULL;
	i = 0;
	while (*token && (*token)->type != PIPE)
	{
		while (*token && (*token)->type == DEFAULT)
		{
			parse->argv[i++] = ft_strdup((*token)->content);
			*token = (*token)->next;
		}
		if (*token && ((*token)->type >= IN && (*token)->type <= APPEND))
			add_redir(token, parse, redir_temp);
		if (*token && (*token)->type == HEREDOC && (*token)->next->content)
		{
			found_here(parse, env, (*token)->next->content);
			(*token) = (*token)->next->next;
		}
		if ((*token) && (*token)->type != PIPE)
			(*token) = (*token)->next;
	}
}

t_parse	*parse(t_token *token, t_env *env)
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
		// token_expand(token, env);
		prep_nod_array(&token, parse_temp, env);
		ft_add_parse(&parse, parse_temp);
		if (token)
			token = token->next;
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

// while (parse_temp->redir_in || parse_temp->redir_out)
// {
// 	if (parse_temp->redir_in)
// 	{
// 		printf("arg '%s' type in '%i' file in '%s' \n", 
//*parse_temp->argv, parse_temp->redir_in->type, 
//parse_temp->redir_in->filename);
// 		parse_temp->redir_in = parse_temp->redir_in->next;
// 	}
// 	else if (parse_temp->redir_out)
// 	{
// 		printf("arg '%s' type out '%i' file out '%s' \n", 
//*parse_temp->argv, parse_temp->redir_out->type, 
//parse_temp->redir_out->filename);
// 		// printf("file out %s \n", parse_temp->redir_out->filename);
// 		parse_temp->redir_out = parse_temp->redir_out->next;
// 	}
// 	// parse->argv++;
// }