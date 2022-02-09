#ifndef ERROR_MESSAGE_H
# define ERROR_MESSAGE_H

# define MISSING_ARGS "Missing arguments.\n"
# define TM_ARGS "Too many arguments.\n"
# define EXPECTED_ARGS "Expected arguments:\n\
\t- number_of_philosophers\n\
\t- time_to_die\n\
\t- time_to_eat\n\
\t- time_to_sleep\n\
\t- [number_of_times_each_philosopher_must_eat] (optional)"
# define INVALID_ARG "Invalid argument value\n"
# define ARG_NBR "Argument number "
# define ARG_STR " should be an integer."
# define ARG_NEG " should be positive."
# define ARG_DIF_0 " shouldn't be equal to 0."
# define MALLOC_ERR "Malloc failed. Your system might be on fire"
# define MUTEX_INIT "Failed to initialize mutex for philosopher number "

#endif
