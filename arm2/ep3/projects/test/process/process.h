//process.h
//Базовый класс для представления понятия "Процесс"
#ifndef PROCESS_H
#define PROCESS_H
#include <unistd.h>

class Process {
public:
Process();
virtual ~Process() {}
operator bool() const; //был ли процесс запущен?
pid_t id() const;
static Process current();
static Process create( int (*function)() );
bool run();
bool kill(int signalNumber);
protected:
virtual int action();
private:
Process(pid_t id);
private:
pid_t pid; //идентификатор процесса
};
inline Process::operator bool() const
{
return pid != 0;
}
inline pid_t Process::id() const
{
return pid;
}

inline int Process::action()
{
return 0;
}
#endif
