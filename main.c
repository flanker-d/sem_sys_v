#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char *argv[])
{
#define SEM_COUNT 16
  key_t key = ftok("/tmp/sem.temp", 1);
  int semid = semget(key, SEM_COUNT, (IPC_CREAT | 0666));
  if(semid == -1)
  {
    perror("Ошибка создания массива семафоров: ");
    return -1;
  }

  struct sembuf sem_ops[SEM_COUNT];
  bzero(&sem_ops, sizeof(struct sembuf) * SEM_COUNT);
  for(int i = 0; i < SEM_COUNT; i++)
  {
    sem_ops[i].sem_num = i;
    sem_ops[i].sem_op = i;
    sem_ops[i].sem_flg = SEM_UNDO;
  }

  return 0;
}
