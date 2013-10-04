#include "ocl_som_types.h"

ocl_som_data::ocl_som_data(int x, int y, int neuron_size)
    : x(x), y(y), neuron_size(neuron_size)
{
    if(x == 0 || y == 0 || neuron_size == 0)
    {
        size = 0;
        data = 0;
    }
    else
    {
        size = x * y * neuron_size;
        data = new float[size];
    }
}

ocl_som_data::~ocl_som_data()
{
    if(data)
        delete[] data;
}

