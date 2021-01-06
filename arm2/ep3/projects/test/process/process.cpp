//process.cpp
#include "process.h"
#include <cstdlib>
#include <signal.h>



pid_t fork()
{

    return 0;
}

Process::Process()
: pid(0)
{}

Process::Process(pid_t id)
: pid(id)
{}

Process Process::current( )
{
return Process(getpid());
}
bool Process::run( )
{
if ( pid )
return false;
pid = fork();
switch ( pid ) {
case -1:pid = 0;return false;
case 0:
pid = getpid();
exit(action());
}
return true;
}

Process Process::create( int (*function)( ) )
{
Process process( fork() );
switch ( process.pid ) {
case -1:
process.pid = 0;
break;
case 0:
exit(function());
}
return process;
}
bool Process::kill( int signalNumber )
{
//return pid ? ::kill(pid, signalNumber) != -1 : false;
return 1;
}
