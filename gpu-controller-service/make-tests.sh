#!/bin/bash
#PBS -l walltime=10:00:00
#PBS -q gpu
#PBS -N gpu_tests

cd $PBS_O_WORKDIR

(./output-receiver) &
for i in $(/bin/ls -1 ../test-models/ | grep "^test-");do
     echo "Using data "$i;
    (./input-sender -d ../test-models/$i) &> $i".msg.log" &
    sleep 5
    (./gpu-controller-service -d ../test-models/$i) &> $i".gpu.log" &
    sleep 5
    echo "Killing everything...."
done

killall output-receiver
