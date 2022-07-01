# TODO
import cs50


def checkValid(number):
    try:
        return isinstance(int(number), int)
    except ValueError:
        return False


def checkDigits(number):
    sum = 0
    tmp = ""

    # Double every other digit starting from second to last
    for i in range(len(number)-2, -1, -2):
        tmp += str(2*int(number[i]))
    # Sum of those digits together not the numbers
    for i in range(len(tmp)):
        sum += int(tmp[i])

    # Sum of those digits that weren't already counted for
    for i in range(len(number)-1, -1, -2):
        sum += int(number[i])

    # Return true if the last digit in the number was 0
    if sum % 10 == 0:
        return True
    else:
        return False


def checkCardType(number):
    # If the first two numbers are [set] and length matches and the digits are valid
    if number[:2] in ["34", "37"] and len(number) == 15 and checkDigits(number):
        print("AMEX")
    elif number[:2] in ["51", "52", "53", "54", "55"] and len(number) == 16 and checkDigits(number):
        print("MASTERCARD")
    elif number[:1] in ["4"] and (len(number) == 16 or len(number) == 13) and checkDigits(number):
        print("VISA")
    else:
        print("INVALID")


def main():
    # Keeps trying to take input until numbers are input
    while True:
        card_num = cs50.get_string("Number: ")
        # If card has only valid inputs then it gets checked
        if checkValid(card_num):
            break
    checkCardType(card_num)


main()