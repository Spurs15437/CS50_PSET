# TODO
from cs50 import get_float

while True:
    owned = get_float("Change owed: ") * 100
    if owned > 0:

        count = 0

        count = count + owned // 25

        owned = owned % 25

        count = count + owned // 10

        owned = owned % 10

        count = count + owned // 5 + owned % 5

        print(int(count))
        break