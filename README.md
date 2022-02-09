## Overview

[![rankstr build and test](https://github.com/ECP-VeloC/rankstr/actions/workflows/build-and-test.yml/badge.svg)](https://github.com/ECP-VeloC/rankstr/actions/workflows/build-and-test.yml)

The rankstr (rank string) library provides functions that identify unique strings across an MPI communicator.

A key use case is to split a communicator into subcommunicators such that all processes in
a resulting subcommunicator consist of those processes that provided an identical input string.
rankstr_mpi_comm_split is a function like MPI_Comm_split, but it takes a variable-length string as the color argument insead of an integer value.

The rankstr_mpi function does not output a communicator, but instead returns a unique integer for each unique string.

For scalability, the implementation uses a distributed, bitonic sort via point-to-point messages
over the input communicator to compare string values.
The caller must provide two distinct tag values that are safe for the function to use for its point-to-point messages.

As an example, one could provide a hostname to split MPI_COMM_WORLD into subcommunicators of
all processes on the same host.

```
#include "rankstr_mpi.h"
...
MPI_Comm newcomm;
char hostname[256];
gethostname(hostname, sizeof(hostname));
rankstr_mpi_comm_split(MPI_COMM_WORLD, hostname, 0, 1, 2, &newcomm);
```

Here, MPI_COMM_WORLD is the input communicator that is to be split,
and the hostname string acts as the color value.
The third parameter (0) is the key, which has the same meaning as in MPI_Comm_split.
The next two parameters (1, 2) are tag values the function will use for its point-to-point messages on the input communicator.
These two tags values must be distinct.
Finally, the resulting communicator is output in newcomm.

For more detailed usage, see [src/rankstr_mpi.h](src/rankstr_mpi.h) and the [User API docs](https://ecp-veloc.github.io/component-user-docs/group__rankstr.html).

## Build

```
cmake -DCMAKE_INSTALL_PREFIX=/path/to/install .
```

## Release

Copyright (c) 2018, Lawrence Livermore National Security, LLC.
Produced at the Lawrence Livermore National Laboratory.
<br>
Copyright (c) 2018, UChicago Argonne LLC, operator of Argonne National Laboratory.


For release details and restrictions, please read the [LICENSE]() and [NOTICE]() files.

`LLNL-CODE-751725` `OCEC-18-060`
