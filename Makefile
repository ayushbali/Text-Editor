# make program allows us to simply run make and will compile the program
# we need to supply a MakeFile to tell how to compile the program

TextEd: TextEd.c # we want to build TextEd from TextEd.c
	$(CC) TextEd.c -o TextEd -Wall -Wextra -pedantic -std=c99

# gcc TextEd.c -o TextEd -Wall -Wextra -pedantic -std=c99: This is the command that will be executed when you want to build the TextEd target.

# $(CC) = is a variable that make expands to cc by default
# -Wall = means all warnings  (the code might not be technically wrong but is considered bad usage of the C language)
# -Wextra and -pedantic = turn on even more warnings
# -std=c99 = the version of C being used which is C99

# to run this makefile use the command make <FileName>