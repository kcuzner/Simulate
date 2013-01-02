#ifndef XMLLOADER_H
#define XMLLOADER_H

#include "interfaces/ifileloader.h"
#include "include/rapidxml.hpp"

/**
 * @brief A file loader which uses RapidXML to load files
 * to and from simulations. Files must have the extension
 * .simx
 */
class XMLFileLoader
{
public:
    XMLFileLoader();

    virtual std::string getFileMatchPattern();

    virtual std::string getFileTypeName();

    virtual boost::shared_ptr<ISimulation> loadFile(ISimulationCore* core, std::string fileName);

    virtual bool saveFile(ISimulationCore*, boost::shared_ptr<ISimulation> simulation, std::string fileName);

    virtual std::string getLastError();

protected:
    void appendDataToBlockNode(rapidxml::xml_document<>* doc, rapidxml::xml_node<>* blockNode, boost::shared_ptr<IBlock> block);
    void attachConnectionsToModel(rapidxml::xml_document<>* doc, rapidxml::xml_node<>* modelNode, char *id, boost::shared_ptr<IBlock> block);
};

#endif // XMLLOADER_H
