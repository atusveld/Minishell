/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:12:23 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/14 12:23:57 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_redir(t_token **temp, t_parse *parse, t_red *redir_temp)
{
	char *filename;

	filename = ft_strdup((*temp)->next->cont);
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

static void	prep_nod_array(t_token **token, t_main *main, t_parse *parse_temp)
{
	int		i;
	t_red	*redir_temp;

	redir_temp = NULL;
	i = 0;
	while (*token && (*token)->type != PIPE)
	{
		while (*token && (*token)->type == DEFAULT)
		{
			parse_temp->argv[i++] = ft_strdup((*token)->cont);
			*token = (*token)->next;
		}
		if (*token && ((*token)->type >= IN && (*token)->type <= APPEND))
			add_redir(token, parse_temp, redir_temp);
		if (*token && (*token)->type == HEREDOC && (*token)->next->cont)
		{
			found_here(main, parse_temp, (*token)->next->cont);
			(*token) = (*token)->next;
		}
		if ((*token) && (*token)->type != PIPE)
			(*token) = (*token)->next;
	}
}

void	parse(t_main *main)
{
	t_parse	*parse;
	t_parse	*parse_temp;
	t_token	*token_pos;

	token_pos = main->token;
	parse = NULL;
	while (main->token)
	{
		parse_temp = ft_calloc(1, sizeof(t_parse));
		parse_temp->argv = ft_calloc(ft_lstsize(main->token) + 1, sizeof(char **));
		token_expand(main);
		prep_nod_array(&main->token, main, parse_temp);
		ft_add_parse(&main->parsed, parse_temp);
		if (main->token)
			main->token = main->token->next;
	}
	main->token = token_pos;
	while (main->token)
	{
		token_pos = main->token->next;
		free(main->token->cont);
		free(main->token);
		main->token = token_pos;
	}
}

	// int i = 0;
	// while (main->parsed)
	// {
	// while (main->parsed->argv[i]) {
	// 	printf("%s\n", main->parsed->argv[i]);
	// 	++i;
	// }
	// main->parsed = main->parsed->next;
	// i = 0;
	// }
	
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