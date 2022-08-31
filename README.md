# Lattice-based verifiable mix-net

Code accompannying the paper "Verifiable Mix-Nets and Distributed Decryption for Voting from Lattice-Based Assumptions".

Depedencies are the [NFLLib](https://github.com/quarkslab/NFLlib) and [FLINT](https://flintlib.org/doc/) 2.8 libraries.
NFLLib is already included in this repository, but instructions for installing its dependencies can be found in the link above.
FLINT is usually included in package managers and can be easily installed in most systems out there.

### Dependencies

To build NFLLib, run the following inside a cloned version of this repository:

```
$ mkdir deps
$ cd deps
$ cmake .. -DCMAKE_BUILD_TYPE=Release -DNFL_OPTIMIZED=ON
$ make
$ make test
```
### Building and running

For building the actual code, run `make` inside the source directory. This will build the binaries for `commit`, `encrypt`, `pianex` and `piaex` and `shuffle` to test and benchmark different modules of the code.

The binaries respectively implement the commitment scheme, the distributed BGV cryptosystem, the two zero-knowledge proofs and the shuffle itself. Tests and benchmarks are included for each of them, such that they can be used independently.

__WARNING__: This is an academic proof of concept, and in particular has not received code review. This implementation is NOT ready for any type of production use.
