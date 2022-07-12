# TODO
from cs50 import get_int
while True:

    number = get_int("Number: ")

    if number > 0:
        middlesum = 0
        number1 = number
        number2 = number
        while number1 > 0:
            temp1 = number1 % 10
            middlesum = middlesum + temp1
            number1 = number1 // 100
        sum1 = middlesum
        middlesum = 0
        number2 = number2 // 10
        while number2 > 0:
            temp2 = number2 % 10
            temp3 = temp2 * 2
            if temp3 >= 10:
                temp4 = temp3 % 10 + (temp3 // 10) % 10
            else:
                temp4 = temp3
            middlesum += temp4
            number2 //= 100
        sum2 = middlesum
        sum = sum1 + sum2
        # print(sum)
        if sum % 10 == 0:
            s = int(str(number)[0:2])
            # print(s)
            n = int(str(number)[0:1])
            # print(n)
            long = len(str(number))
            # print(long)
            if long == 15 and (s == 34 or s == 37):
                print('AMEX')
            elif (long == 13 or long == 16) and n == 4:
                print('VISA')
            elif long == 16 and (s > 50 and s < 56):
                print('MASTERCARD')
            else:
                print("INVALID")
        else:
            print("INVALID")

        break