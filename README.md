## About The Project

This project is intended to provide an easy-to-use framework for linux application development.

## Requirements

Required packages and installation commands

   ```sh
   # Note: These commands are for a debian linux flavor
   #       For Centos, use the 'sudo yum install [package]' command
   sudo apt-get install cmake # Note: Need cmake3 
   sudo apt-get install make
   sudo apt-get install gcc-c++
   sudo apt-get install libasound-dev # This allows audio recording and playback
   ```

## Building the project

This section will provide instructions for building the project on a linux system

1. Clone the repo
   ```sh
   git clone https://github.com/experiencedgambino/development-framework.git
   ```
2. Go to the cloned directory
   ```sh
   cd development-framework
   ```
3. Make the build directory
   ```sh
   mkdir build
   ```
4. Build the project 
   ```sh
   cmake ..
   make
   ```
