/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

(cmd sh)

{
	int	ret;
	int	i;

	i = 0;
	while (i < _numberOfSimpleCommands)
	{
		i++;
		ret = fork();
		if (ret == 0)
		{
			//child
			execvp(sCom[i]->args[0], sCom[i]->_args);
			perror("execvp");
			_exit(1);
		}
		else if (ret < 0)
		{
			perror("fork");
			return;
		}
	}
		// Parent shell continue
	if (!background)
	{
		// wait for last process
		waitpid(ret, NULL);
	}
} // execute

void	Command: :execute()
{
	//save in/out
	int	tmpin = dup(0);
	int	tmpout = dup(1);

	//set the initial input
	int	fdin;
	if (infile)
		fdin = open(infile, O_READ);
	else
		fdin = dup(tmpin);
	
	int	ret;
	int	fdout;
	int	i;

	i = 0;
	while (i < numsimplecommands)
	{
		i++;
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (i == numsimplecommands - 1)
		{
			// Last simple command
			if (outfile)
				fdout = open(outfile, WTF)
			else
				// use default output
				fdout = dup(tmpout);
		}
	}

	else
	{
		// Not last
		//simple command
		//create pipe
		int	fdpipe[2];
		pipe(fdpipe);
		fdout = fdpipe[1];
		fdin = fdpipe[0];
	}//if/else

	//Redirect output
	dup2(fdout, 1);
	close(fdout);

	// Create child process
	ret = fork();
	if (ret == 0)
	{
		execvp(scmd[i].args[0], scmd[i].args);
		perror("execvp");
		_exit(1);
	} //  for
	
	//restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	if (!background)
	{
		// Wait for last command
		waitpid(ret, NULL);
	}
} //  execute