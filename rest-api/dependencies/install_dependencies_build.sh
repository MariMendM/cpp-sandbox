#!/bin/bash

#Full dependencies for dev and compilation
sudo apt install libboost-filesystem-dev libcpprest-dev -y
#Removing packages automatically installed and that are no longer required
sudo apt autoremove -y