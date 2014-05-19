#!/usr/bin/python

from numpy import *
import numpy.random as nr
from functools import partial
from optparse import OptionParser
import sys
import os
import os.path
import datetime

usage = 'Usage: %prog NR-INPUT NR-HIDDEN NR-OUTPUT'
parser = OptionParser(usage=usage)
parser.add_option('-n', '--name', help='Test case name (default: numbers of neurons per layer joined by hyphens)')
# TODO: add option for choosing activation function
# TODO: add option for setting upper and lower limits for the weights
# TODO: add option for setting non-random inputs
options, args = parser.parse_args()

if len(args) < 3 or not all(arg.isdigit() for arg in args):
    parser.print_help()
    sys.exit(1)

model_name = options.name if options.name else '-'.join(args[:3])
if os.path.exists(model_name):
    sys.stderr.write('Model %s already exists. Please choose a different name\n' % model_name)
    sys.exit(2)

def logistic(x):
    return 1. / (1.0 + exp(-x))

def scale(x, a, b):
    return a + (b - a) * x

n_input, n_hidden, n_output = map(int, args[:3])

extended_input = scale(nr.random(n_input + 1) - 0.5, -1, 1)
extended_input[-1] = 1
input = extended_input[:-1]

weights_ih = scale(nr.random((n_hidden, n_input + 1)),  -0.001,  0.001)
weights_ho = scale(nr.random((n_output, n_hidden + 1)), -0.001,  0.001)

extended_hidden = empty(n_hidden + 1)
hidden = extended_hidden[:-1]
hidden[:] = dot(weights_ih, extended_input)
hidden[:] = logistic(hidden)

output = dot(weights_ho, extended_hidden)
output = logistic(output)

os.mkdir(model_name)

savetxt = partial(savetxt, fmt='%1.6f')
savetxt(model_name + '/input.txt',  input)
savetxt(model_name + '/hidden.txt', hidden)
savetxt(model_name + '/output.txt', output)
savetxt(model_name + '/weights_ih.txt', weights_ih)
savetxt(model_name + '/weights_ho.txt', weights_ho)

now = datetime.datetime.now()
timestamp = now.strftime('%Y/%m/%d %H:%M:%S')
with open(model_name + '/info.txt', 'w') as info_file:
    info_file.writelines([
        'Model: %s\n' % model_name,
        'Generated on: %s.\n' % timestamp,
        'Command line was: %s' % ' '.join(sys.argv),
        '\n',
        '%d input neurons\n' % n_input,
        '%d hidden neurons\n' % n_hidden,
        '%d output neurons\n' % n_output,
        '\n',
        'weights_ih.txt: %d x %d matrix\n' % (n_hidden, n_input + 1),
        'Element in (row i, column h) is the weight between input neuron i and hidden neuron h.\n',
        'The rightmost column has the biases for each of the hidden neurons.\n',
        '\n'
        'weights_ho.txt: %d x %d matrix\n' % (n_output, n_hidden + 1),
        'Element in (row h, column j) is the weight between hidden neuron h and output neuron j.\n',
        'The rightmost column has the biases for each of the output neurons.\n',
        '\n'
        'input.txt: test input for the %d input neurons.\n' % n_input,
        'hidden.txt: values of the %d hidden neurons for the test input.\n' % n_hidden,
        'output.txt: output of the %d output neurons for the test input.\n' % n_output,
    ])

