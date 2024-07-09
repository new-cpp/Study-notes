import random

def hello_age():
    print('what is your age') # comment
    age = int(input())
    print('you age will be in one year :' + str((age)+1)) 


    if(age > 30 and age < 40):
        print('you are old')
    elif (age > 40):
        print('too old')
    else :
        print('here is first then fabonichi series:')

        u0 = 1
        u1 = 1
        iteration = 0

        while( iteration <  11):
                print(u0)
                prev = u0
                u0 = u1
                u1 = u1 + prev
                iteration = iteration + 1

hello_age()


def loop():
    for i in range(5):
        print(i)
    print()

    for i in range(9 , 15):
     print(i)

    print('multiple of three')
    for i in range(3, 9, 3):
     print(i)


    print('random numbers')
    for i in range(5):
     print(random.randint(1,10))
loop()
