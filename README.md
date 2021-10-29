# Philosophers

This is a 42 school project about multi-threading and mutex.  
The goal is to implement the Dining Philosopher's Problem.  

> I've never thought philosophy would be so deadly - Random person who wrote the subject.

###### Version of the subject : 9

## Definition of the problem

The problem is as follow :
- There is a defined number of philosopher around a round table.
- They are doing one of three things: eating, thinking or sleeping.
- Their actions are defined as such :
	- While eating, they are not thinking or sleeping.
	- While sleeping, they are not eating or thinking.
	- While thinking, they are not eating or sleeping.
- There is a large bowl of spaghetti in the center.
- There is a fork between each of them.
- They can only eat  with two forks (?when they hold both the left and right forks.?) 
- They must never be starving.
- They all need to eat.
- They are completly silent, they can't communicate with each other.
- When a philosopher has finished eating, he will drop his forks and sleep
- When a philosopher is done sleeping, he will start thinking.

## Some requirement of the project

- The simulation stops when a philosopher dies.
- The programe takes a set number of arguments :
	- number_of_philosophers
	- time_to_die (in milliseconds)
	- time_to_eat (in milliseconds)
	- time_to_sleep (in milliseconds)
	- \[number_of_times_each_philosopher_must_eat\](optional)
- Each philosopher should be given a number from 1 to 'number_of_philosophers'.
- Philosopher number 1 is next to philosopher number 'number_of_philosophers'.
Any other philosopher with the number N is seated between philosopher N - 1 and
philosopher N + 1
- Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)
	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is sleeping
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died
- The status printed should not be scrambled or intertwined with another philoso-
pher’s status.
- You can’t have more than 10 ms between the death of a philosopher and when it
will print its death.
- One fork between each philosopher, therefore if they are multiple philosophers,
	there will be a fork at the right and the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state
	with a mutex for each of them.
- Each philosophers should be a thread.

## Other ressources

[External functions allowed](docs/external_functions.md)  
[Some notes i took](docs/personal_notes.md)
