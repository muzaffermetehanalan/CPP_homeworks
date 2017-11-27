#ifndef MYEX_H
#define MYEX_H
#include <exception>
#include <iostream>
using namespace std;
class myException : public exception {
	public:
		myException(const char* message) : badMessage(message) { }
		virtual const char * what()const throw() {
			return badMessage;
		}
	private:
		const char* badMessage;
};

#endif
