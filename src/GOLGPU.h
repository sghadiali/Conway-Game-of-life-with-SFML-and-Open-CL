#pragma once
#include "GOL.h"
#include "OpenCLHelper.h"
class GOLGpu : public GOL
{
public:
	GOLGpu() {};
private:
	virtual void initialize() override;
	virtual void calculateGol() override;

	cl::Program program;
	cl::Kernel gol_cl;
	cl::Context context;
	cl::Buffer newValBuf;
	cl::Buffer oldValBuf;
	cl::Device devices;
	cl::CommandQueue queue;
	cl_int err;
};