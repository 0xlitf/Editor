#ifndef PROPERTY_GLOBAL_H
#define PROPERTY_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PROPERTY_LIB
# define PROPERTY_EXPORT Q_DECL_EXPORT
#else
# define PROPERTY_EXPORT Q_DECL_IMPORT
#endif

#endif // PROPERTY_GLOBAL_H
