#include "model_wrapper.h"
#include <iostream>

int main()
{
    try
    {
        double parameter;
        std::cin >> parameter;
        ModelWrapper model;

        model.ImportModel("../examples/test.ply");

        model.SmoothSharpLedges(parameter);

        model.ExportModel("ply", "../examples/out.ply");
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}