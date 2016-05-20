/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL os interface
**/

#pragma once

#if defined(_MSC_VER)
#define ECAL_OS_WINDOWS
#endif

#if defined(__GNUC__)
#define ECAL_OS_LINUX
#endif
