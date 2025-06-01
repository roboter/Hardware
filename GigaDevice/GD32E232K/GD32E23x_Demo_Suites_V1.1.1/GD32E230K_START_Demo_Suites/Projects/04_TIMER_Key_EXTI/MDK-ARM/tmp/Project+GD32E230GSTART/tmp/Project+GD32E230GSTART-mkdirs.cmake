# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART")
  file(MAKE_DIRECTORY "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART")
endif()
file(MAKE_DIRECTORY
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/1"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART/tmp"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART/src/Project+GD32E230GSTART-stamp"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART/src"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART/src/Project+GD32E230GSTART-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART/src/Project+GD32E230GSTART-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230K_START_Demo_Suites/Projects/04_TIMER_Key_EXTI/MDK-ARM/tmp/Project+GD32E230GSTART/src/Project+GD32E230GSTART-stamp${cfgdir}") # cfgdir has leading slash
endif()
