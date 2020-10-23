#include "mpi.h"
#include "rankstr_mpi.h"
#include <stdio.h>

int alltrue(int valid, MPI_Comm comm)
{
  int all_valid;
  MPI_Allreduce(&valid, &all_valid, 1, MPI_INT, MPI_LAND, comm);
  return all_valid;
}

int main(int argc, char* argv[])
{
  int rc = 0;

  MPI_Comm comm = MPI_COMM_WORLD;

  MPI_Init(&argc, &argv);

  int rank, ranks;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &ranks);

  int newrank, newranks;
  MPI_Comm newcomm;

  char str[1024];
  snprintf(str, sizeof(str), "%d", rank);
  int groups, groupid;

//Since the unique input string to rankstr_mpi is the rank of the process,
//there are going to be as many unique strings as processes. Therefore groups=ranks.
  rankstr_mpi(str, comm, 0, 1, &groups, &groupid);
  if (! alltrue(groups == ranks, comm)) {
    if (rank == 0) {
      printf("test_rankstr, full split failed");
      printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    }
    return 1;
  }

//Since unique input string is rank, each newcomm should contain
//just 1 process (same as the calling process)
  rankstr_mpi_comm_split(comm, str, 0, 0, 1, &newcomm);
  MPI_Comm_rank(newcomm, &newrank);
  MPI_Comm_size(newcomm, &newranks);
  MPI_Comm_free(&newcomm);
  if (! alltrue(newrank == 0 && newranks == 1, comm)) {
    if (rank == 0) {
      printf("test_rankstr, full comm split failed");
      printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    }
    return 1;
  }

//Since the unique input string to rankstr_mpi is empty,
//all processes will be associated with the same (empty) string. Therefore groups=1.
  rankstr_mpi("", comm, 0, 1, &groups, &groupid);
  if (! alltrue(groups == 1, comm)) {
    if (rank == 0) {
      printf("test_rankstr, no split failed");
      printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    }
    return 1;
  }

//Since all precesses are associated with the same group,
//newcomm is the same as comm.
  rankstr_mpi_comm_split(comm, "", 0, 0, 1, &newcomm);
  MPI_Comm_rank(newcomm, &newrank);
  MPI_Comm_size(newcomm, &newranks);
  MPI_Comm_free(&newcomm);
  if (! alltrue(newrank == rank && newranks == ranks, comm)) {
    if (rank == 0) {
      printf("test_rankstr, no comm split failed");
      printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    }
    return 1;
  }


  MPI_Finalize();

  return rc;
}
