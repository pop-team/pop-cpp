#
# Root file for cmake test compilation with POP-C++
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(test-cmake NONE)
ENABLE_LANGUAGE(POPCPP)

SUBDIRS(barrier classparam constparam heritageparam2  matrixNB  param serialize_vect templateparam vectorint1 vectorx callback exception heritageparam1 jobManager method passparam structparam tree vectorint2)
