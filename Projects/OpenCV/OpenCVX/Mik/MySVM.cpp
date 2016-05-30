#include "MySVM.h"

MySVM::MySVM()
{
}

void MySVM::create()
{
	this->machine = SVM::create();
	this->machine->setType(SVM::Types::C_SVC);
	
	/* for finding number plates */
	//this->machine->setKernel(SVM::KernelTypes::RBF);
	//this->machine->setC(2);
	//this->machine->setGamma(1.2);

	/* for finding letters */
	this->machine->setKernel(SVM::KernelTypes::LINEAR);
	this->machine->setC(0.00001);
	this->machine->setGamma(0.1);
}


MySVM::~MySVM()
{
}
