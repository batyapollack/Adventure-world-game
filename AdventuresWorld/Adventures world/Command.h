
#pragma once
//-----------------Command----------------------------------------
class Command
{
public:
	virtual ~Command() {} //virtual Dtor 
	virtual void execute() = 0; //virtual execute

};