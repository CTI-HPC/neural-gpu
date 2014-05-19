Integral, parte 1
=================
La tarea consiste en
estimar numéricamente
el valor de la integral definida:

.. math::

    \int_{-4}^{4} e^{-x/16} \cos^2\bigl(2\pi f(x) x\bigr)\,dx,

donde:

.. math::

    f(x) = \frac{1}{10} \sum_{i = 0}^{9} k\bigl(x - (-3.3 + 0.7i)\bigr)

y:

.. math::

    k(x) = 0.5 + \frac{1.5}{1 + 50x^2},

usando el `método de Simpson`_
con `n = 2^{22}` subintervalos.

.. _método de Simpson: http://es.wikipedia.org/wiki/Regla_de_Simpson

Para la primera parte de esta tarea,
no hay que calcular la integral completamente en la GPU.
Lo que hay que hacer es:

* dividir el dominio de integración en `M` subdominios,
* asignar cada subdominio a un bloque de hebras,
* hacer que las hebras calculen *en paralelo*
  y usando memoria compartida,
  el valor de la integral en cada subdominio,
* poner el resultado de cada subdominio
  en una casilla de un arreglo global.

Archivos de la tarea
--------------------
El `código base`_ contiene:

* ``integral-cpu.cpp``: implementación de referencia
  del método de Simpson en C++, para entender el algoritmo
  y comparar los resultados.
* ``integral.cu``: esqueleto del programa en CUDA.
* ``plot.py``: script que grafica la función a integrar
  y calcula el resultado de la integral usando SciPy.
* ``Makefile``.

.. _código base: _static/integral.tgz

Qué hay que hacer
-----------------
* Escribir el programa CUDA que calcula las `M` partes de la integral
  y las guarda en un arreglo global.
* Medir cómo influye el tamaño del bloque
  en el tiempo de ejecución del programa.

