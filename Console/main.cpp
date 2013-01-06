#include <QCoreApplication>

#include "simulationcore.h"

#include <iostream>

void displayHelp();

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Error: Too few arguments" << std::endl;
        displayHelp();
        return -1;
    }

    //load all the plugins in the plugin folder

    //process the command line arguments

    //load the simulation they want us to load
    boost::shared_ptr<ISimulation> simulation = SimulationCore::getInstance()->loadSimulation(argv[argc-1]);
    if (!simulation)
    {
        std::cout << "Error: Could not load simulation. Last error: " << SimulationCore::getInstance()->getLastFileError();
        return -1;
    }

    //set up the simulation
    boost::shared_ptr<IEngine> engine = SimulationCore::getInstance()->createEngine(simulation);

    std::cout << "Running " << argv[argc-1] << ":" << std::endl;
    std::cout << "\tSteps: " << engine->getStepsToRun() << std::endl;
    std::cout << "\tDelta: " << engine->getStepDelta() << std::endl;

    //run the simulation
    std::cout << "\nRunning simulation..." << std::endl;
    engine->run();

    std::cout << "Simulation finished." << std::endl;

    return 0;
}

void displayHelp()
{
    std::cout << "Simulate CLI" << std::endl;
    std::cout << "Usage:\n\tsimulate-cli [options] file.simx" << std::endl;
    std::cout << "Options:\n\t-h\t\tShows this message" << std::endl;
    std::cout << "\t-e [name]\tUses the specified engine" << std::endl;
}
