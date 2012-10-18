#include <stdio.h>

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h> 
#include <unistd.h>
#include <semaphore.h>

#define SHMSZ     27

int main(int argc, char **argv)
{
  printf("K Computer basic function test started\n");
  
  char c;
  int shmid;
  key_t key;
  char *shm, *s;
  sem_t *sem;
  char* name = (char*)"sem1234";
  sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 0);
  if (sem == SEM_FAILED) {
    printf("Error opening semaphore\n");
  }

  
  key = 1234;
  
  // Create the shared memory segment
  if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
    perror("shmget");
    return 1;
  }
  
  pid_t pid = fork();

  if(pid ==0) {
    printf("I'm the child, my pid %d , my ppid %d\n", getpid(), getppid());
    char* argv1[3];
    argv1[0] = (char*)"sideprogram";
    argv1[1] = (char*)"1234";
    argv1[2] = name;
    argv1[3] = (char*)0;
    execv(argv1[0], argv1);
    perror("Execv failed");

  } else if(pid != -1) {
    printf("I'm the parent process, my pid %d, my ppid %d\n", getpid(), getppid());
    int status;

    // Attaching the segment to this data space
    if ((shm = (char*)shmat(shmid, NULL, 0)) == (char*)-1) {
      perror("shmat");
      return 1;
    }
    
    if(sem_wait(sem) == -1){
      perror("sem_wait");      
    }
    
    s = shm;

    // Write smth into the memory segment
    for (c = 'a'; c <= 'z'; c++) {
      *s++ = c;
    }
    *s = '\0';    
    if(sem_post(sem) == -1){
      perror("sem_post");    
    }
    
    if(sem_wait(sem) == -1){
      perror("sem_wait");    
    }
    
    s = shm;
    
    for (s = shm; *s != '\0'; s++){
      putchar(*s);
    }
    putchar('\n');  
    
    
    waitpid(pid, &status, 0);
    
#ifdef __LINUX__    
    if(sem_destroy(sem) == -1){
      perror("sem_destroy");
    }
#endif
      
    if (-1 == sem_unlink(name)) {
      perror("sem_unlink");
    }

    // detach from the segment
    if (shmdt(shm) == -1) {
      perror("shmdt");
      return 1;
    }
    
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
      perror("shmctl");
      return 1;
    }
    
  } else {
    perror("erreur");
    return 1;
  }
  printf("K Computer basic function test ended\n");
}