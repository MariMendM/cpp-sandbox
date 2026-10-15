#!/bin/bash

#Runtime dependencies, to be installed in case the app is dinamically compiled (without -static option)
sudo apt remove libboost-filesystem1.90.0 libcpprest2.10 -y
#Removing packages automatically installed and that are no longer required
sudo apt autoremove -y