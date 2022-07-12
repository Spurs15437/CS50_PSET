# TODO
while True:
    try:
        height = int(input('Height: '))
        if height > 0 and height < 9:
            for i in range(height):
                print(' ' * (height - i - 1), end='')
                print('#' * (i + 1))
            break
    except ValueError:
        print("Please input a number!")

