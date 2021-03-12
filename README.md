# Philosophers

42 project about the dining philosophers problem, to learn basics of threading and processes.

## Final grade : 100/100

Mandatory part : 100/100

## philo_one

Philosopher with threads and mutex.

## philo_two

Philosopher with threads and semaphore.

## philo_three

Philosopher with processes and semaphore.

## How to run

Use `make` to build `philo_XXXX`

```
./philo_XXXX <nb philos> <time to die> <time to eat> <time to sleep> [nb eat] (<mendatory> | [optional])
```

## Tests

No one should die:

```
./philo_XXXX 4 410 200 200
./philo_XXXX 5 800 200 200
```

A philosopher should die:

```
./philo_XXXX 4 310 200 100
./philo_XXXX 5 410 200 200
./philo_XXXX 2 60 60 60
```
