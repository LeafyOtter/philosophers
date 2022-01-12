# Notes philosophers

### Calculating time_to_think

```
time_to_die > time_to_eat + time_to_sleep + time_to_think  
arg > arg + arg	+ to_calculate  

time_to_die - time_to_eat - time_to_sleep > time_to_think  
```

### Sketching up some stuff i guess

```
for n equals to an even integer

for n philosophers
time_to_die > time_to_eat + time_to_sleep + time_to_think

for n + 1 philosophers
time_to_die > (2 * time_to_eat) + time_to_sleep + time_to_think

edit : both of those are wrongs.

for n philosophers :
time_to_die > time_to_eat + max(time_to_eat, time_to_sleep)
for n + 1 philosophers :
time_to_die > time_to_eat + max(time_to_eat * 2, time_to_sleep)
```

the first time_to_eat is the time the philo takes to eat.  
the second (and third) correspond to the time other philos take to eat.  
the time_to_sleep is the time the philo sleep.  
max() is used to get the higher value,
because if time_to_eat is higher than time_to_sleep,
it will need to think a longer time.


- Different timing if nbr of philosophers is even or not.
- A philosopher dies after time_to_die, except if they eat.
- Time to die is counted since last time they ate or beginning of simulation;

### Smart Locking (cant implement)

this method would work for an odd number of philosophers, i'm gonna need
to test it on an even number.  

so for n number of philosophers (and by extension n number of forks)
- nth philosophers would lock (n - 1)th fork.
- two philosophers (for exemple 0 and 1) would race to lock 0
	- one them would be blocked
- unblocked philosophers tries to lock the nth fork.
	- if the fork is already lock, unlock the other fork
	- try locking nth fork again, if already locked, the philo is blocked
	- try locking (n - 1)th fork, if already locked, the philo is blocked

if my maths are correct, this would enable (n / 2) philosophers
to eat simultanely, and ((n / 2) + 1) philosophers to wait.


### References

[Dining philosophers rebooted, by Howard E. Hinnant](https://howardhinnant.github.io/dining_philosophers.html)
