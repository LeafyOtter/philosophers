# External functions

This is a list of the external functions authorized for this project.

| function name         | description                    | system library |
|:---------------------:|:------------------------------:|:--------------:|
| memset                | fill memory with constant byte | string.h       |
| printf                | print formated                 | stdio.h        |
| malloc                | allocate memory                | stdlib.h       |
| free                  | free memory                    | stdlib.h       |
| write                 | write to a fd                  | unistd.h       |
| usleep                | sleep for n microsec           | unistd.h       |
| gettimeofday          | get date and time              | sys/time.h     |
| pthread_create        | create new thread              | pthread.h      |
| pthread_detach        | detach a thread                | pthread.h      |
| pthread_join          | wait for thread to finish      | pthread.h      |
| pthread_mutex_init    | reinit a destroyed mutex       | pthread.h      |
| pthread_mutex_destroy | destroy and init a mutex       | pthread.h      |
| pthread_mutex_lock    | lock a mutex                   | pthread.h      |
| pthread_mutex_unlock  | unlock a mutex                 | pthread.h      |
