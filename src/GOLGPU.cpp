#include "GOLGPU.h"
#include <iostream>


void GOLGpu::initialize()
{
	program = createProgram("golGPU.cl");
	err = program.build("-cl-std=CL1.2");
	gol_cl = cl::Kernel(program, "devGolGenerate");

	std::cout << gol_cl.getInfo<CL_KERNEL_FUNCTION_NAME>() << std::endl;
	std::cout << gol_cl.getInfo<CL_KERNEL_NUM_ARGS>() << std::endl;

	err = program.getInfo(CL_PROGRAM_CONTEXT, &context);

	//Creating memory buffers
	oldValBuf = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, W * H * sizeof(bool), oldVal, &err);
	newValBuf = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, W * H * sizeof(bool), newVal, &err);

	//Set Kernel args
	err = gol_cl.setArg(0, oldValBuf);
	err = gol_cl.setArg(1, newValBuf);
	err = gol_cl.setArg(2, W);
	err = gol_cl.setArg(3, H);

	//getting device to make queue
	program.getInfo(CL_PROGRAM_DEVICES, &devices);
	std::cout << devices.getInfo<CL_DEVICE_NAME>() << std::endl;

	//Getting command queue
	queue = cl::CommandQueue(context, devices, 0, &err);
}

void GOLGpu::calculateGol()
{
	err = queue.enqueueWriteBuffer(oldValBuf, CL_TRUE, 0, sizeof(bool) * W * H, oldVal);
	err = queue.enqueueWriteBuffer(newValBuf, CL_TRUE, 0, sizeof(bool) * W * H, newVal);
	cl::NDRange global = { H * W };
	err = queue.enqueueNDRangeKernel(gol_cl, 0, global);
	err = queue.enqueueReadBuffer(newValBuf, CL_TRUE, 0, sizeof(bool) * W * H, newVal);
	err = queue.finish();
}
