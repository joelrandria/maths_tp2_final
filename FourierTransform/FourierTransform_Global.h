#ifndef FOURIERTRANSFORM_GLOBAL_H
#define FOURIERTRANSFORM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FOURIERTRANSFORM_LIBRARY)
#  define FOURIERTRANSFORMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FOURIERTRANSFORMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FOURIERTRANSFORM_GLOBAL_H
