enum State {ASLEEP = 0, EATING};

int philosopher_process(int num,char ** argv);

void kill_philosopher();

void create_philosopher();

void take_fork(int phnum);

void put_fork(int phnum);

void test(int phnum);

int left (int phnum);

int right (int phnum);

void sleep();