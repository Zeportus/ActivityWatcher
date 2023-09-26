# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/zepor/source/repos/ActivityWatcherCMake/out/build/x64-debug/_deps/zlib-src"
  "C:/Users/zepor/source/repos/ActivityWatcherCMake/out/build/x64-debug/_deps/zlib-build"
  "C:/Users/zepor/source/repos/ActivityWatcherCMake/out/build/x64-debug/_deps/zlib-subbuild/zlib-populate-prefix"
  "C:/Users/zepor/source/repos/ActivityWatcherCMake/out/build/x64-debug/_deps/zlib-subbuild/zlib-populate-prefix/tmp"
  "C:/Users/zepor/source/repos/ActivityWatcherCMake/out/build/x64-debug/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp"
  "C:/Users/zepor/source/repos/ActivityWatcherCMake/out/build/x64-debug/_deps/zlib-subbuild/zlib-populate-prefix/src"
  "C:/Users/zepor/source/repos/ActivityWatcherCMake/out/build/x64-debug/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/zepor/source/repos/ActivityWatcherCMake/out/build/x64-debug/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp/${subDir}")
endforeach()
