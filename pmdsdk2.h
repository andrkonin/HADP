/*****************************************************************************
 * PMDSDK 2
 * 
 * Copyright (c) 2006-2012 PMD Technologies GmbH
 * All Rights Reserved.
 *
 * Author: Martin Profittlich
 *
 *****************************************************************************/
#pragma once
#include <pmddatadescription.h>

extern "C" {

typedef unsigned PMDHandle;
int pmdOpen (PMDHandle * hnd, const char * rplugin, const char * rparam, const char * pplugin, const char * pparam);
        unsigned numOut, struct PMDDataDescription * ddOut, void ** output, size_t * maxLen, unsigned * type, 
        unsigned numIn, struct PMDDataDescription * ddIn, void ** input);

#ifndef PMD_NO_DEPRECATED
int pmdConnect (PMDHandle * hnd, const char * rplugin, const char * rparam, const char * pplugin, const char * pparam);

#endif 

}