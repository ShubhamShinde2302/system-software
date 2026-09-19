#include<stdio.h>

extern char **environ;

int main(){
	
	char **env = environ;

	while(*env != NULL){
		printf("%s\n", *env);
		env++;
	}

	return 0;

}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_15.c -o question_15
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_15
SHELL=/bin/bash
SESSION_MANAGER=local/shubham-Nitro-ANV15-52:@/tmp/.ICE-unix/2184,unix/shubham-Nitro-ANV15-52:/tmp/.ICE-unix/2184
QT_ACCESSIBILITY=1
COLORTERM=truecolor
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
XDG_MENU_PREFIX=gnome-
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
LANGUAGE=en_IN:en
GNOME_SHELL_SESSION_MODE=ubuntu
SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
XMODIFIERS=@im=ibus
DESKTOP_SESSION=ubuntu
GTK_MODULES=gail:atk-bridge
PWD=/home/shubham/Desktop/LINUX
LOGNAME=shubham
XDG_SESSION_DESKTOP=ubuntu
XDG_SESSION_TYPE=wayland
HOME=/home/shubham
USERNAME=shubham
LANG=en_IN.UTF-8
XDG_CURRENT_DESKTOP=ubuntu:GNOME
VTE_VERSION=7600
TERM=xterm-256color
USER=shubham
DISPLAY=:0
SHLVL=1
XDG_RUNTIME_DIR=/run/user/1000
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
OLDPWD=/home/shubham/Desktop
_=./question_15

Note: this list is the environment of the shell that started the program, so
it differs from machine to machine and from session to session. The same list
can be confirmed with the "env" or "printenv" command. Adding a variable
before the command adds a line to the output:

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ MYVAR=hello ./question_15 | grep MYVAR
MYVAR=hello

==================================================== */
