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
  int i = 0;
  for(i = 0; i < SEM_COUNT; i++)
  {
    sem_ops[i].sem_num = i;
    sem_ops[i].sem_op = i;
    sem_ops[i].sem_flg = 0;
  }
  int res = semop(semid, sem_ops, SEM_COUNT);
  if(res  == -1)
  {
    perror("Ошибка инициализации семафоров: ");
    return -1;
  }

  return 0;
}
