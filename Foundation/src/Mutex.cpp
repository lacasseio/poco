//
// Mutex.cpp
//
// $Id: //poco/1.4/Foundation/src/Mutex.cpp#2 $
//
// Library: Foundation
// Package: Threading
// Module:  Mutex
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Mutex.h"


#if defined(POCO_ENABLE_CPP11) && (POCO_OS != POCO_OS_CYGWIN)
#include "Mutex_STD.cpp"
#elif defined(POCO_OS_FAMILY_WINDOWS)
#if defined(_WIN32_WCE)
#include "Mutex_WINCE.cpp"
#else
#include "Mutex_WIN32.cpp"
#endif
#elif defined(POCO_VXWORKS)
#include "Mutex_VX.cpp"
#else
#include "Mutex_POSIX.cpp"
#endif


namespace Poco {


Mutex::Mutex(MutexType type)
	: MutexImpl((MutexTypeImpl) type)
{
}


Mutex::~Mutex()
{
}


FastMutex::FastMutex()
{
}


FastMutex::~FastMutex()
{
}


} // namespace Poco
