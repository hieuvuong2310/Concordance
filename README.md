# Concordance
**OVERVIEW**

_________________________________________________________________________________________________________________________________________________________________________________
This project will solve a problem involving a tool used by many research and scholars that is called a concordance. Specifically we will consider one kind of concordance known as keyword-out-of-context.

As an example, consider the following small text file. Line numbers are given for your reference.

This is the input file

***************************************************************************************************

the fish a dog cat dog rabbit

the fish and cat

a rabbit or elephant

***************************************************************************************************

After running the program from the command line: _./concord3 in14.txt -e english-2.txt_ or _./concord3 -e latin-2.txt in19.txt_ after calling _make_ from the command line

***************************************************************************************************
CAT	     the fish a dog cat dog rabbit (1)

CAT      the fish and cat (2)

DOG      the fish a dog cat dog rabbit (1*)

ELEPHANT a rabbit or elephant (3)

FISH     the fish a dog cat dog rabbit (1)

FISH     the fish and cat (2)

RABBIT   the fish a dog cat dog rabbit (1)

RABBIT   a rabbit or elephant (3)

***************************************************************************************************

• You	may	assume	that	keywords	will	be	at	most	40	characters	long,	and	you	may	use a	compile-time	constant	to	represent	this.

• You	may	assume	the	length	of	any	input	line	will	be	at	most	100	characters.

• Words	with	identical	spelling	but	different	lettercase were	considered	the	same	keyword


**FILE CLARIFICATION**

_________________________________________________________________________________________________________________________________________________________________________________
• concord3.c:	The	majority	of	my	solution	will	most	likely	appear	in	this	file.	

• emalloc.[ch]: Code	for	safe	calls	to	malloc(). If there were error with malloc(), the program would terminate.

• seng265-list.[ch]:	Type	definitions,	prototypes,	and	code for	the	singlylinked	list	implementation.

• makefile:	This	automates	many	of	the	steps	required	to	build	the	concord3

• referencefile: contains 6 language files to refer to

• testfile: contains 21 testing input files

• expectfile: all outputs after running all the testfile are expect to be the same as 21 expected files in this folder
