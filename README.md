HTTP-1.0-Proxy
==============

For CS3103

Running the proxy

Requirements
- Boost
- g++ or some form of a C++ compiler

Instructions for running on MacOSX 10.8.2
=========================================
1. Install homebrew on your system by running the following command in terminal
ruby -e "$(curl -fsSkL raw.github.com/mxcl/homebrew/go."

2. Install boost on your system by running the following command in terminal.
brew install boost

3. cd to the directory containing the code. 

4. Type make in the command line and the code will be compiled

5. Type ./proxy to run the program.

6. Arguments are port num and filter filename, in order. Default is port 7777 and filter.dat

Instructions for running on Windows
===================================
1. Download the Boost 1.51 installer from http://www.boostpro.com/download/

2. Install boost using the installer downloaded.

3. Open a Visual Studio project, and add all the *.cpp and *.h files

4. Go to Project->Properties->Configuration Properties->C/C++->General under Additional Include Directories add path to your boost includes.
(e.g. D:\apps\boost\boost_1_51)

5. Go to Project->Properties->Configuration Properties->Linker->General under Additional Library Dependencies add path to your boost lib directory.
(e.g. D:\apps\boost\boost_1_51\lib)

6. Press run.

Disclaimer: Configuration not tested because boost is not yet available for VS2012

Instruction for running on most *nix flavours
=============================================
1. Install Boost with precompiled headers on your system using your favourite package manager. For example
yum install boost-devel

2. cd to the directory containing the code. 

3. Edit Makefile such that the string after -L is the absolute path to the boost libraries.

4. Type make in the command line and the code will be compiled.

5. Type ./proxy to run the program.

6. Arguments are port num and filter filename, in order. Default is port 7777 and filter.dat