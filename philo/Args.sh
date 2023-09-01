./philo 1 800 200 200  okay
./philo 5 800 200 200 okay
./philo 5 800 200 200 7 without valgrind there is no death but with valgrind there is
./philo 4 410 200 200 no death
./philo 4 310 200 100 death occurred
./philo 2 500 250 250

commands:
valgrind  --tool=drd
 valgrind --tool=helgrind 
valgrind --tool=drd 
valgrind --leak-check=yes

./philo 5 800 200 200 7 | grep "is eating" | wc -l
valgrind ./philo 5 800 200 200 7

check above arguments with helgrind and with just valgrind.
Check the times as well no more than 10ms. Also check with tool=drd

