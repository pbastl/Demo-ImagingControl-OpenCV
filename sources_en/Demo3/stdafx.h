// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently




#pragma once

#define OPENCV
#ifdef OPENCV
#pragma unmanaged
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\core\types_c.h"
#include "opencv2\ml.hpp"
#pragma managed
#endif

#include <tisudshl.h>		// Hlavièka knihovny IC Imaging Control
#include "listener.h"

