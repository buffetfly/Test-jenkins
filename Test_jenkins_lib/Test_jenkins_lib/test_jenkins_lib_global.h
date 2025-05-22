#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(TEST_JENKINS_LIB_LIB)
#  define TEST_JENKINS_LIB_EXPORT Q_DECL_EXPORT
# else
#  define TEST_JENKINS_LIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define TEST_JENKINS_LIB_EXPORT
#endif
