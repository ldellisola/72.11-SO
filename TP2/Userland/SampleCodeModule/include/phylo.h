enum State {ASLEEP = 0, EATING};

int philosopher_process();

void kill_philosopher();

void create_philosopher();

// char * philo_p_name (int phnum);

// char * philo_sem_name (int phnum);

void take_fork(int phnum);

void put_fork(int phnum);

void test(int phnum);

int left (int phnum);

int right (int phnum);