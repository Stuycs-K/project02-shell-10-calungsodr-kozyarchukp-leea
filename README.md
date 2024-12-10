[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell
Group 14CharsOrMore  
Members: Raechel Calungsodr, Polina Kozyarchuk, Anastasia Lee

Implemented features:  
- prompt (prints cwd)
- takes in user input  
- can execute programs (ls, echo, cowsay, etc.)  
- can handle cd  
- can handle exit  
- can handle EOF  
- simple redirection:  
   - one < / >
   - a composition of only < > 
- simple pipes:
   - one |  
   - composition of | and < / >
  
Bugs and issues:  
- N/A
  
Function headers:  
//takes string line, puts all the space-separated pieces into argary  
void parse_args( char * line, char ** arg_ary );  

//prints errno  
void err();  

//prints terminal, parses, calls pipes and redirect when necessary  
int main(int argc, char * argv[]);  

//prints cwd path and parses user input. returns array of commands from user input  
char ** prompt();  

//executes a pipe given char** args (user input separated into an array)  
void piping(char** args);

//executes cd given char ** args (user input separated into an array). returns 0 on success  
int cd(char ** args);     

// prints char **  
void printchars(char ** arr);    

//takes int ind and char** args, removes index ind from args  
void removeArg(char** args, int ind);  

//executes redirect, given char** args (user input separated into an array)   
void redirect(char** args); 

//takes in char **, iterates through and returns the index of "<" if found and 0 otherwise   
int containsA(char ** args); 

//takes in char **, iterates through and returns the index of ">" if found and 0 otherwise   
int containsB(char ** args);
