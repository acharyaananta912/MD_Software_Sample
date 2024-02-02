'''
This file consists two functions:
1. bin2int (it converts binary to integer)
2. int2bin (it converts integer to binary)
'''
def bin2int(bin_string):

    '''
    This function takes 16-bit binary number in Two's Complement representation 
    as a string and converts it to a integer number using the following formula:
    -a*2^15 + sum(a_i*2^(i)), i ranges from 0-14 and a_i is the ith element of the binary number.
    For example, if the input is "1111111100000010", the output is -254, which follows the following steps:
    ______________________________________________________________________________________________
    | -32768 | 16384 | 8192 | 4096 | 2048 | 1024 | 512 | 256 | 128 | 64 | 32 | 16 | 8 | 4 | 2 | 1 | = bin_to_int_converter
    |    *   |   *   |   *  |   *  |   *  |   *  |  *  |  *  |  *  |  * |  * |  * | * | * | * | * |     
    |    1   |   1   |  1   |   1  |  1   |  1   |  1  |  1  |  0  |  0 |  0 |  0 | 0 | 0 | 1 | 0 | = bin_string
    -----------------------------------------------------------------------------------------------
    | -32768 + 16384 + 8192 + 4096 + 2048 + 1024 + 512 + 256 +  0  + 0  + 0  + 0  + 0 + 0 + 2 + 0 | = integer = -254
    -----------------------------------------------------------------------------------------------
    '''
    # making sure input is a string, its length is 16, and it consists only 0s and 1s
    assert(type(bin_string)==str)
    assert(len(bin_string)==16)
    assert all(char == "0" or char == "1" for char in bin_string)
    

    # converts each elements of "bin_string" into integer and lists them
    bin_list = [int(x) for x in list(bin_string)] 

    # makes a multiplier for 16-bit Two's complement binary to integer conversion
    bin_to_int_converter = [2**(x-1) for x in list(range(16,0,-1))]

    # Converts the first element of the binary multiplier to a negative number.
    bin_to_int_converter[0] = -1*bin_to_int_converter[0]

    # Elementwise multiplies the digits of input with a binary to conversion list and sums them all
    integer = sum(list(map(lambda x,y: x * y, bin_list, bin_to_int_converter)))

    return integer


def int2bin(x):

    '''
    This function takes a integer and converts it to a 16-bit binary number in 
    Two's Complement representation as a string.
    For example, if the input is -254, the output is "1111111100000010", which follows the following steps:
    ____________________________________________________________________________________________________________
    | -254
    | 32768 |-16384 | -8192 | -4096 | -2048 | -1024 | -512 | -256 | -128 | -64 | -32 | -16 | -8 | -4 | -2 | -1 | = pw
    | 32768 | 32514 | 16130 |  7938 |  3842 |  1794 |  770 |  258 |  2   |  2  |  2  |  2  |  2 |  2 |  2 |  0 | = xmod
    ------------------------------------------------------------------------------------------------------------
    |   1   |   1   |   1   |   1   |   1   |   1   |   1  |   1  |  0   |  0  |  0  |  0  |  0 |  0 |  1 |  0 | = z = "1111111100000010"
    ------------------------------------------------------------------------------------------------------------
    and for 254, the output is "0000000011111110", which follows the following steps:
    ____________________________________________________________________________________________________________
    | 254
    | 32768 |-16384 | -8192 | -4096 | -2048 | -1024 | -512 | -256 | -128 | -64 | -32 | -16 | -8 | -4 | -2 | -1 | = pw
    | 254   |  254  |  254  |  254  |  254  |  254  |  254 |  254 |  254 | 126 |  62 |  30 | 14 |  6 |  2 |  0 | = xmod
    ------------------------------------------------------------------------------------------------------------
    |  0    |   0   |   0   |   0   |   0   |   0   |   0  |   0  |   1  |  1  |  1  |  1  |  1 |  1 |  1 |  0 | = z = "0000000011111110"
    ------------------------------------------------------------------------------------------------------------
    '''

    # making sure input is an integer and within the range of 16-bit binary number
    # upper bound is 2^15-1 = 32767 and lower bound is -2^15 = -32768
    assert(type(x)==int)
    assert(x>=-32768 and x<=32767)


    # Empty list is initialized
    bin_string = [] 

    if x==0:

        # If input is 0, outputs 16 0s, i.e "000000000000"
        for n in range(0,16):
            bin_string.append("0")

    else:
        if x<0:
            # if input is a negative number then the first digit of binary representation is set 1
            tmp = "1"
            # converting negative number to positive number by adding 2^15 (total number integers 16-bit binary number including positive and negative numbers)
            xmod = x + 2**15
        else:

            # if input is a positive number then the first digit of binary representation is set 0
            tmp = "0"
            xmod = x
        # adds "0" or "1" as the first element of the list depending on sign of the number (-ve = "1", +ve = "0")
        bin_string.append(tmp)
        
        for n in range(1,16):

            # pw is the power of 2, i.e 2^15, 2^14, ... ..., 2^0
            pw = 2**(15-n)

            # z is the quotient of xmod/pw, it is always 0 or 1, when quotient exceeds 1, the number cannot be represented in 16-bit binary number
            z = int(xmod/pw)

            # xmod is the remainder of xmod/pw if z =1, and no change if z = 0.
            xmod = xmod - z*pw

            # tmp is the string version of z
            tmp = str(z)
            
            # adds tmp to the list
            bin_string.append(tmp)
    # joins the string elements of the list to make a string
    bin_string = ''.join(bin_string)

    return bin_string


def bin2add(bin1, bin2):
    """
    Adds two binary numbers represented as strings.

    Parameters:
    - bin1 (str): The first binary number.
    - bin2 (str): The second binary number.

    Returns:
    - str: The sum of the two binary numbers.

    Description:
    This function takes two binary numbers as input and performs binary addition digit by digit.
    It starts from the right and moves towards the left.
    The carry is initialized to 0.
    For each bit position, the function calculates the sum of the corresponding bits of bin1, bin2, and the carry.
    If the sum is 0, the output bit is 0 and the carry is set to 0.
    If the sum is 1, the output bit is 1 and the carry is set to 0.
    If the sum is 2, the output bit is 0 and the carry is set to 1.
    If the sum is 3, the output bit is 1 and the carry is set to 1.
    Finally, the output bits are reversed and joined to form the sum of the two binary numbers.
    """

    # Checks if each inputs have 16-digits, checks if elements of the strings are "0"s or "1"s
    assert(len(bin1)==16 and len(bin2)==16)
    assert(all(x in ['0','1'] for x in bin1))
    assert(all(x in ['0','1'] for x in bin2))

    bin_out = []
    carry = 0

    # Perform binary addition digit by digit
    for i in range(15, -1, -1):
        total_sum = int(bin1[i]) + int(bin2[i]) + carry

        if total_sum == 0:
            bin_out.append("0")
            carry = 0
        elif total_sum == 1:
            bin_out.append("1")
            carry = 0
        elif total_sum == 2:
            carry = 1
            bin_out.append("0")
        elif total_sum == 3:
            carry = 1
            bin_out.append("1")
    

    # Reverse the output bits and join them to form the sum
    bin_out = "".join(bin_out)
    return bin_out[::-1]

if __name__ == "__main__":

    print("\nTesting bin2int function:")

    try:
        integer = bin2int("hello")
    except AssertionError:
        print("Input Error: 'hello' does not satisfy one/more than one input requirements.")

    try:
        binary = int2bin("1100110011")
    except AssertionError:
        print("Input Error: '1100110011' does not satisfy one/more than one input requirements.")

    try:
        binary = int2bin("1100110011001102")
    except AssertionError:
        print("Input Error: '1100110011001102' does not satisfy one/more than one input requirements.")
    
    print("\n'1000000000000000' = ",bin2int("1000000000000000"))
    print("'1110110001111000' = ",bin2int("1110110001111000"))
    print("'0000000000000000' = ",bin2int("0000000000000000"))
    print("'0001001110001000' = ",bin2int("0001001110001000"))
    print("'0111111111111111' = ",bin2int("0111111111111111"))
    
    print("\n\nTesting int2bin function:")

    try:
        binary = int2bin("hello")
    except AssertionError:
        print("Input Error: 'hello' is not an integer.")

    try:
        binary = int2bin(-32769)
    except AssertionError:
        print("Input Error: -32769 is less than the lower bound of a 16-bit binary number.")

    try:
        binary = int2bin(32768)
    except AssertionError:
        print("Input Error: 32768 is greater than the upper bound of a 16-bit binary number.")
    
    
    print("\n-32768 = ",int2bin(-32768))
    print("-5000 = ",int2bin(-5000))
    print("0 = ",int2bin(0))
    print("5000 = ",int2bin(5000))
    print("32767  = ",int2bin(32767))

    print("\n\nTesting add2bins function:")
    try:
        bin_out = add2bins("hello", "110110")
    except AssertionError:
        print("Input Error: ('hello','110110') doesn't satisfy input requirement.")

    try:
        bin_out = add2bins(12345, 54321)
    except AssertionError:
        print("Input Error: (12345, 54321) doesn't satisfy input requirement.")

    try:
        bin_out = add2bins("10010", 54321)
    except AssertionError:
        print("Input Error: (12345, 54321) doesn't satisfy input requirement.")

    print("\nAdding ('1111111100000000','1001110001000'): ", add2bins('1111111100000000','1001110001000'))
    print("Adding ('1111011000','101111011'): ", add2bins('1111011000','101111011'))
    print("Adding ('1111111111111111','1111111111111111'): ", add2bins('1111111111111111','1111111111111111'))


