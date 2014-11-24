POP-C++ 2.5
===========

BEFORE STARTING
---------------

In order to install properly POP-C++ from source, you will need following software:

* C++ compiler
* GNU make
* Flex / Bison. (optional: for parser modification only)
* zlib

COMPILE POP-C++ SOURCE CODE
---------------------------

.. code::

  user@computer$ cmake .

Once the configuration script is done.

.. code::

  user@computer$ make

INSTALLING POP-C++
------------------

.. code::

  user@computer$ make install

You might use sudo or to be root tu execute "make install" if you do not have the right to write in the destination folder.

The installation script will ask you several questions. Here they are:

1. DO YOU WANT TO CONFIGURE POP-C++ SERVICES? (y/n)

You can configure the POP-C++ Global Services by answering "y" to this question.

2. DO YOU WANT TO MAKE A SIMPLE INSTALLATION ? (y/n)

If you answered "y" at the 1st question, you will be asked if you want to make a simple installation. The simple installation will set the default parameters. If you want to parameterize the POP-C++ Global Services, answer "n".

TESTING YOUR INSTALLATION
-------------------------

The release directory contains a test suite. This test suite is located under ./test

You can execute the test suite by running the "runtests" script with the "-all" option.

.. code::

  user@computer$ ./runtests -all
