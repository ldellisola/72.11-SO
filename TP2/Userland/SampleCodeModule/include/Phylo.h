// void * philosopher_process(void * num);

int philosopher_process(int num, char ** argv);

void kill_philosopher(int i);

void create_philosopher(int i);

// char * philo_p_name (int phnum);

// char * philo_sem_name (int phnum);

void take_fork(int phnum);

void put_fork(int phnum);

void test(int phnum);

int left (int phnum);

int right (int phnum);