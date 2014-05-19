Diferencias finitas
===================

Escriba un programa usando CUDA
que calcule las diferencias finitas ``d`` de un arreglo ``a``.

Si ``a`` es un arreglo de tamaño ``N``,
entonces ``d`` debe ser un arreglo de tamaño ``N - 1``,
cuyos elementos deben satisfacer::

    d[i] = a[i + 1] - a[i]

Experimente para determinar qué tamaño ``N`` debe tener el arreglo
para que la GPU le gane a la CPU al hacer la misma tarea.

A continuación,
reimplemente su programa usando memoria compartida.
Cada bloque de hebras debe copiar a su memoria compartida
los datos con los que trabajará.

Nuevamente, experimente para determinar qué tamaño ``N`` debe tener el arreglo
para que la GPU le gane a la CPU al hacer la misma tarea.

