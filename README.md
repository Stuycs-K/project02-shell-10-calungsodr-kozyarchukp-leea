[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell
Group 14CharsOrMore  
Members: Raechel Calungsod, Polina Kozyarchuk, Anastasia Lee

Implemented features:  
- prints cwd (unless input is from a file)  
- takes in user input  
- can execute programs (ls, echo, cowsay, etc.)  
- can handle cd  
- can handle exit  
- can handle EOF  
- can handle simple redirection with:  
   - one < / >
   - a composition of only < > 
   - one |  
  
Bugs and issues:  
- cannot handle a composition of | and </>  (ex. cat < lines.txt | wc > wc.txt), "No such file or directory" error

  
Function headers:  
// takes string line, separates the string by spaces and places into array of strings. returns the separated array.
void parse_args( char * line, char ** arg_ary )  

// prints errno  
int err();  

// prints terminal, parses, calls pipes and redirects when necessary
// user input, loops until exited
int main(int argc, char * argv[]);  

//prints cwd path and parses user input. returns array of commands from stdin
char ** prompt();  

// uses redirecting to a temp file to execute a command with a pipe given char** args (stdin separated into an array)
void piping(char** args);  

// executes cd given char ** args (stdin separated into an array), returns 0
int cd(char ** args);     

//takes int ind and char** args, shifts values to remove index ind from args
void removeArg(char** args, int ind);  

// given stdin in the format of an array of strings, executes redirect
void redirect(char** args);