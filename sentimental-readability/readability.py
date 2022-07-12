# TODO
import cs50

userinput = cs50.get_string("Text: ")

count_letters = 0
count_blank = 1
count_sentences = 0
for i in userinput:
    if i.isalnum():
        count_letters += 1
    elif i == '?' or i == '!':
        count_sentences += 1
    elif i == '.':
        count_sentences += 1
    elif i == ' ':
        count_blank += 1
# print(count_letters)

sen1 = 100.00 * count_letters / count_blank
sen2 = 100.00 * count_sentences / count_blank

index = 0.0588 * sen1 - 0.296 * sen2 - 15.8

if index < 1:
    print('Before Grade 1')
elif index > 16:
    print('Grade 16+')
else:
    # k = index.round()
    print(f'Grade {round(index)}')