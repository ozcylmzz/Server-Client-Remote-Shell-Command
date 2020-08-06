# Server Client Remote Shell Command
 
Consists of two parts as a server and client.
Shell commands entered from the client are run on the server-side computer and run
results are retransmitted to the client. Arguments when running the server and client
must be in the right order. User name when logging in to the server side: user,
password: must be entered as pass. User and pass are defined in code. To be replaced
if desired, the code must be changed from within. Two users are identified on the client side. Simple
for an authentication purpose, the user name in a text file as a user database
and passwords are kept. Users defined here cannot be made external input. This
users are defined as “zct 123” and “ozcan 321”. Password or username
error will prevent entry into the system.

You can compile server.c as “gcc server.c -o UKSU_server”. After that you can execute with
"./UKSU_server -p 4040 -u user-p" command.

On the server side;
The login function uses the user name and password that the client entered in the user database
compares with users and returns the result back.
The shell_execute function runs the command given as a parameter to it and returns the
returns the result. I planned to do it with Fork and execvp functions, but
execvp does not return the result back. So the popen () function with the command
is run and the result is obtained.

You can compile “gcc client.c -o UKSU_client”. After that you can execute with
"./UKSU_client -h www.yildiz.edu.tr -p 4040 -u zct -p 123".
There is no function on the client side. If the connection with the server is successful, the client
can execute any commands until the user has entered the “exit” command.

Server software allows only one client to connect to itself at any time
will provide.

![1](https://user-images.githubusercontent.com/34898893/89551957-364a3580-d814-11ea-9b6e-be0a12c70e9c.PNG)
![2](https://user-images.githubusercontent.com/34898893/89551959-377b6280-d814-11ea-9051-37679178b27b.PNG)
![3](https://user-images.githubusercontent.com/34898893/89551963-3813f900-d814-11ea-8e99-3bc0b187c779.PNG)
![4](https://user-images.githubusercontent.com/34898893/89551945-33e7db80-d814-11ea-8c5f-888c00fc7eec.PNG)
![5](https://user-images.githubusercontent.com/34898893/89551952-34807200-d814-11ea-9945-6c6bc9319858.PNG)
![6](https://user-images.githubusercontent.com/34898893/89551954-35b19f00-d814-11ea-91f8-b84bc6a020e7.PNG)
