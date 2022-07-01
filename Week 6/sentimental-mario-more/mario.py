# TODO
import cs50

def make(blanks, blocks):
    if blanks == 0:
        return

    blanks -= 1
    blocks += 1

    print(" " * blanks, end = "")
    print("#" * blocks, end = "  ")
    print("#" * blocks)
    make(blanks, blocks)


# Ask for height of pyramid
while True:
    height = cs50.get_int("Input height of pyramid: ")
    if height >= 1 and height <= 8:
        break

make(height, 0)