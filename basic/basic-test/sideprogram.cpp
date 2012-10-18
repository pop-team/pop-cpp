#include <stdio.h>

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h> 
#include <sys/ipc.h>
#include <semaphore.h>

#define SHMSZ     27


int main(int argc, char **argv)
{
  printf("Side program started\n");
  
  
  int shmid;
  key_t key;
  char *shm, *s;
  sem_t *sem;  
  
  key = atoi(argv[1]);
  
  sem = sem_open(argv[2], O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
  if (sem == SEM_FAILED) {
    printf("Error opening semaphore\n");
  }
  
  sem_post(sem);
  
  printf("Side program started %d\n", key);
  if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
    perror("shmget");
    return 1;
  }

  //Now we attach the segment to our data space.
  if ((shm = (char*)shmat(shmid, NULL, 0)) == (char *) -1) {
    perror("shmat");
    return 1;
  }

  if (sem_wait(sem) == -1) {
    printf("Error locking semaphore\n");
  }

  // Now read what the server put in the memory.
  for (s = shm; *s != '\0'; s++){
    putchar(*s);
    *s = '*';
  }
  putchar('\n');  

  if (sem_post(sem) == -1) {
    printf("Error unlocking semaphore\n");
  }
  
  // detach from the segment
  if (shmdt(shm) == -1) {
    perror("shmdt");
    return 1;
  }

  
  printf("Side program ended\n");
  return 0;
}