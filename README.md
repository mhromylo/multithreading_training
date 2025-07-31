<h1 align="center"> 🍴 Solving "Dining Philosophers Problem" throught multhy threading.</h1>

Problem Statement
The Dining Philosopher Problem involves 'n' philosophers sitting around a circular table. Each philosopher alternates between two states: thinking and eating. To eat, a philosopher needs two chopsticks, one on their left and one on their right. However, the number of chopsticks is equal to the number of philosophers, and each chopstick is shared between two neighboring philosophers.

The standard problem considers the value of 'n' as 5 i.e. we deal with 5 Philosophers sitting around a circular table.

Constraints and Conditions for the Problem
Every Philosopher needs two forks to eat.
Every Philosopher may pick up the forks on the left or right but only one fork at once.
Philosophers only eat when they have two forks. We have to design such a protocol i.e. pre and post protocol which ensures that a philosopher only eats if he or she has two forks.
Each fork is either clean or dirty.
