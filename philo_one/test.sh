make

MUST_EAT=10
NB_TESTS=10
RESULT=0

for ((i=0 ; i < NB_TESTS ; i++)); do
	./philo_one 4 410 200 200 $MUST_EAT > out
	< out grep eat > eat
	< eat grep "1 is eating" > one
	< eat grep "2 is eating" > two
	< eat grep "3 is eating" > three
	< eat grep "4 is eating" > four
	ONE=$(wc -l one | awk '{print $1}')
	TWO=$(wc -l two | awk '{print $1}')
	THREE=$(wc -l three | awk '{print $1}')
	FOUR=$(wc -l four | awk '{print $1}')
	if [ $ONE -ge $MUST_EAT ] && [ $TWO -ge $MUST_EAT ] && [ $THREE -ge $MUST_EAT ] && [ $FOUR -ge $MUST_EAT ]
	then
		printf "+"
		((++RESULT))
	else
		printf "-"
		printf "Error at test number $i\n\n" > error.txt
		printf "One $ONE\n" >> error.txt
		printf "Two $TWO\n" >> error.txt
		printf "Three $THREE\n" >> error.txt
		printf "FOUR $FOUR\n\n" >> error.txt
		printf "Eat log:\n" >> error.txt
		eat >> error.txt
		printf "\n\n" >> error.txt
	fi
	rm one two three four
	rm out
done
printf "\nResult $RESULT / $NB_TESTS\n";
