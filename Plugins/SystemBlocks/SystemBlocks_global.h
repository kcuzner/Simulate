#ifndef SYSTEMBLOCKS_GLOBAL_H
#define SYSTEMBLOCKS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SYSTEMBLOCKS_LIBRARY)
#  define SYSTEMBLOCKSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SYSTEMBLOCKSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SYSTEMBLOCKS_GLOBAL_H
