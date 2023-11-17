import sys
import re


def main():
    card = card_input()
    check_number_digit(card)
    check_luhn(card)


def card_input():
    while True:
        try:
            card = input("Number: ")
            if len(card) > 0 and int(card):
                break
        except ValueError:
            print("INVALID")
    return card


def check_number_digit(card):
    if len(card) not in (13, 15, 16):
        print("INVALID")
        exit()
    else:
        return card


def check_luhn(card):
    digits = [int(x) for x in card]

    # convert digits to select the second-to-last easily
    # second-to-last become second-from-begin
    digits = digits[::-1]

    even = digits[1::2]

    odd = digits[0::2]

    sum_even = 0
    for number in even:
        sum_even += (number * 2 // 10) + (number * 2 % 10)

    sum_odd = 0
    sum_odd += sum(odd)

    total = 0
    total = sum_even + sum_odd

    if total % 10 != 0:
        print("INVALID")
        return

    start_of_card = int(card[:2])

    if start_of_card in (51, 52, 53, 54, 55) and len(card) == 16:
        print("MASTERCARD")
    elif start_of_card in (34, 37) and len(card) == 15:
        print("AMEX")
    elif start_of_card // 10 == 4 and len(card) in (13, 16):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
