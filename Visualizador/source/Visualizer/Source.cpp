#include <memory>

#include "Visualizer.h"
#include "Utility.h"

#include <iostream>
#include <cstring>

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

using namespace Library;

int main(int argc, char** args)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Utility::SetWorkingDirectoryFromArgs(args);

	///std::cout << Utility::GetWorkingDirectory() << std::endl;

	/** args:
	execucao, densidade, semente, desvio padrao,
        caminho para o arquivo de ponto de controle
        método de resolver a floresta
	LOAD
	l 15 1 10 ../../forests/solution/forest_solution_dir_0.3_30_15_10.txt
	MANUAL e RUN_SCRIPT
	m 15 1 10 DIRECT
	*/
	std::unique_ptr<Visualizer> renderer (new Visualizer("Renderer Tests", args));
	try
	{
	    //std::cout<<"try"<<std::endl;
		renderer->Run();
	}
	catch (RendererException ex)
	{
		std::cerr << "ERROR: " << ex.what() << std::endl;
	}

    std::cin.get();

	return 0;
}
