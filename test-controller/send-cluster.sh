#!/bin/bash
#PBS -l walltime=10:00:00
#PBS -q gpumpi
#PBS -N gpu_controller_prototype

hostname
cd $PBS_O_WORKDIR
./test-controller

