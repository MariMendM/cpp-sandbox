#!/bin/bash

#Full dependencies for dev and compilation
sudo apt remove libboost-filesystem-dev libcpprest-dev -y
#Removing packages automatically installed and that are no longer required
sudo apt autoremove -y