/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.10.0 distribution.
  *
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  


#ifndef STM32F7INSTRUMENTATION_HPP
#define STM32F7INSTRUMENTATION_HPP

#include <platform/core/MCUInstrumentation.hpp>
#include <stdint.h>

namespace touchgfx
{
class STM32F7Instrumentation: public MCUInstrumentation
{
public:
    virtual void init();
    virtual unsigned int getElapsedUS(unsigned int start, unsigned int now, unsigned int clockfrequency);
    virtual unsigned int getCPUCycles();
    virtual void setMCUActive(bool active);
};

} // namespace touchgfx

#endif // STM32F7INSTRUMENTATION_HPP
