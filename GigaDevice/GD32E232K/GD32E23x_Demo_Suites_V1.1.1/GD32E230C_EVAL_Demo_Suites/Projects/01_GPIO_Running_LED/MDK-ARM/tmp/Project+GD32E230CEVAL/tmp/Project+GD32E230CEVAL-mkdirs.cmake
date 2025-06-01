# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL")
  file(MAKE_DIRECTORY "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL")
endif()
file(MAKE_DIRECTORY
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/1"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL/tmp"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL/src/Project+GD32E230CEVAL-stamp"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL/src"
  "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL/src/Project+GD32E230CEVAL-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL/src/Project+GD32E230CEVAL-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/PROJECTS/Hardware/GigaDevice/GD32E232K/GD32E23x_Demo_Suites_V1.1.1/GD32E230C_EVAL_Demo_Suites/Projects/01_GPIO_Running_LED/MDK-ARM/tmp/Project+GD32E230CEVAL/src/Project+GD32E230CEVAL-stamp${cfgdir}") # cfgdir has leading slash
endif()
