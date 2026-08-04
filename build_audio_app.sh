#!/bin/bash
# Script to build audio_app image
# Author: Sebastien Banon.

cd meta-aesd/audio_app
make clean
make audio_app
