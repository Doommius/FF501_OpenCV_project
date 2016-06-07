#include "MySVM.h"

MySVM::MySVM()
{
}

void MySVM::create()
{
	this->machine = SVM::create();
	this->machine->setType(SVM::Types::C_SVC);
	this->machine->setKernel(SVM::KernelTypes::RBF);
	//this->machine->setC(2);
	//this->machine->setGamma(1.2);
}


MySVM::~MySVM()
{
}
