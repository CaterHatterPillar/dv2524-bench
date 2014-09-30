dv2524-bench
============

A set of OpenGL ES 2.0 benchmarks for Linux X11 and Android systems.
The benchmarks were originally used to profile paravirtualized graphics acceleration in the Simics full-system simulator that I devised for my master's thesis, which may be read [here](https://github.com/CaterHatterPillar/dv2524).

The set of benchmarks attempt to stress computational complexity and API function invocation latency and bandwidth with three respective benchmarks:

* Julia
* Chess
* Phong

![alt text](https://github.com/CaterHatterPillar/dv2524-bench/blob/master/img/imgjulia.png "Julia benchmark")

![alt text](https://github.com/CaterHatterPillar/dv2524-bench/blob/master/img/imgchess.png "Chess benchmark")

![alt text](https://github.com/CaterHatterPillar/dv2524-bench/blob/master/img/imgphong.png "Phong benchmark")

The set uses the [Newell teapot model and texture](http://graphics.cs.williams.edu/data/meshes.xml) devised by Kenzie Lamar; courtesy of Morgan McGuire's, hosted at Williams College, in addition to the [color palette](http://nuclear.mutantstargoat.com/articles/sdr_fract/) by John Tsiombikas.

Licensed under the GNU General Public License.