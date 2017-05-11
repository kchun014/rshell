## RShell €
This program is meant to simulate bash shell

It uses a euro sign instead of a $ in order to show that it's not the standard shell.

It contains a unique exit command in "Done"

Created and maintained by Kau Chung and Andre Cuevas.

## Features
-All usr/bin commands

-logical operators

    examples:
	
        i) a || b
		
		>command 'b' will run only if command 'a' failed.
		
        ii) a && b
        
		>command 'b' will run only if command 'a' runs.
		
-flag extensions

-highly optimized exit commands

-now including git commands!

-Custom end command (Done)


## Tests
Tested various combinations of commands, logical operators, end statements, and exit calls.

Attached to folder.

## Contributors

Kau Chung

Andre Cuevas

stackoverflow

Cplusplusreference

Boost::Technologies

Brian Craites


## License


GNU GENERAL PUBLIC LICENSE
Version 3, 29 June 2007
Copyright © 2007 Free Software Foundation, Inc. <http://fsf.org/>
Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.

Bugs: 
i) No error given when boolean operators are stacked (i.e. || && || &&)

ii) no error given when only one argument given of logical operators (||, &&, ;).

iii) does not work when semicolons are in the middle of an argument 

	(i.e. echo he;llo will echo "he;llo", when it should output he and give an error for "llo")

iv) mkdir does not execute "or" commands after failure, if file already exists.

v) using commands with logical operators, then ending with done crashes the shell.

vi) Cannot use echo with multiple terms (i.e. echo "Hello everybody")
