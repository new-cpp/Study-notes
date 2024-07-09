# function with paramters

# None value return type of functions without return statement

# global statement : inside a function to refer to the global variable instead of createing a local one
# global x

# execption example:
# once the execution line is out of try close it's don't return

#in the first example the line of execution continue

def spam(devideBy):
    try:
        return 42/devideBy
    except ZeroDivisionError:
        print('Error : invalid arg')


print(spam(3))
print(spam(2))
print(spam(0))
print(spam(3))


def spam_1(devideBy):
    return 42/devideBy 

try:
    print(spam_1(2))
    print(spam_1(0))
    print(spam_1(3))

except ZeroDivisionError:
    print('Error : Invalid Argument')




#collatz

def collatz(number):
    if number %2 == 0:
        number = number //2
    else:
        number = 3*number + 1
    
    return number


try:
    number = int(input('enter a number'))
    while number != 1:
        number = collatz(number)
        print(number)

except ValueError:
    print('enter a number')
 
# my_zigzag

def print_line(space_cnt):
    for i in range(space_cnt):
        print(' ',end='')
    print('**********')

def my_zigzag():
    space = 4
    direction = -1
    while(True):
        
        if(direction==1 and space == 4):
            direction = -1
        elif ( direction == -1 and space == 0):
            direction =1

        print_line(space)
        space += direction

        
#my_zigzag()

# their example ,mine better :'( 

import sys,time


def zigzag():

    indent = 0
    indentIncrease = True

    try:
        while(True):
            print(' ' * indent, end='')
            print('*' * 8)
            time.sleep(0.1)

            if indentIncrease:
                indent = indent + 1
                if(indent == 20):
                    indentIncrease = False
            else: 
                indent = indent - 1
                if(indent == 0):
                    indentIncrease = True
    except KeyboardInterrupt:
        sys.exit()


zigzag()
