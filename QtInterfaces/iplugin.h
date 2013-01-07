#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QString>

/**
 * @brief IPlugin class that forms the base for any plugin
 */
class IPlugin
{
public:
	virtual ~IPlugin() { }

	virtual QString getPluginName() = 0;
	virtual QString getAuthorName() = 0;
	virtual QString getManufacturerName() = 0;
	virtual QString getVersion() = 0;
	virtual QString getLicenseName() = 0;
	virtual QString getCopyright() = 0;
	virtual QString getNotes();
};

#endif
