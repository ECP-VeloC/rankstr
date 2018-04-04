/*
 * Copyright (c) 2009, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by Adam Moody <moody20@llnl.gov>.
 * LLNL-CODE-411039.
 * All rights reserved.
 * This file is part of The Scalable Checkpoint / Restart (SCR) library.
 * For details, see https://sourceforge.net/projects/scalablecr/
 * Please also read this file: LICENSE.TXT.
*/

#ifndef RANKSTR_MPI_H
#define RANKSTR_MPI_H

/* Given a communicator and a string, compute number of unique strings
 * across all procs in comm and compute an id for input string
 * such that the id value matches another process if and only if that
 * process specified an identical string. The groupid value will range
 * from 0 to groups-1. */
void rankstr_mpi(
  const char* str, /* IN  - input string (pointer) */
  MPI_Comm comm,   /* IN  - communicator of processes (handle) */
  int tag1,        /* IN  - tag to use for point-to-point communication on comm */
  int tag2,        /* IN  - another tag, distinct from tag1, for point-to-point on comm */
  int* groups,     /* OUT - number of unique strings (non-negative integer) */
  int* groupid     /* OUT - id for input string (non-negative integer) */
);

/* split input comm into sub communicators, each of which contains
 * all procs specifying the same value of str, and reordered according
 * to key, ranks providing str == NULL will return newcomm == MPI_COMM_NULL */
void rankstr_mpi_comm_split(
  MPI_Comm comm,    /* IN  - communicator of processes (handle) */
  const char* str,  /* IN  - input string (pointer) */
  int key,          /* IN  - key to order ranks in new communicator */
  int tag1,         /* IN  - tag to use for point-to-point communication on comm */
  int tag2,         /* IN  - another tag, distinct from tag1, for point-to-point on comm */
  MPI_Comm* newcomm /* OUT - output communicator */
);

#endif
