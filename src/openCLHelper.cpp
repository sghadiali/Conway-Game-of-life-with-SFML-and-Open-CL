#include <CL/cl.hpp>
#include <fstream>
#include <iostream>

cl::Program createProgram(const char* fileName)
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Platform plat = cl::Platform();
    if (platforms.size() > 0)
        plat = platforms[0]; // pick the first platform that's found
    else
    {
        printf("no OpenCL platform found\n");
        exit(0);
    }

    std::vector<cl::Device> devices;
    plat.getDevices(CL_DEVICE_TYPE_GPU, &devices);

    printf("Found %d devices\n", devices.size());

    cl::Context context = cl::Context(devices[0]);

    printf("Context Info:\n");
    std::vector<cl::Device> dev = context.getInfo<CL_CONTEXT_DEVICES>();
    std::cout << devices[0].getInfo<CL_DEVICE_NAME>() << std::endl;

    cl::CommandQueue q = cl::CommandQueue(context, devices[0], 0);

    //read file
    //std::string fileName = "vec_add.cl";

    std::ifstream programFile(fileName);

    std::string src(std::istreambuf_iterator<char>(programFile), (std::istreambuf_iterator<char>()));

    cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));
    cl::Program program(context, sources);
    return program;

}