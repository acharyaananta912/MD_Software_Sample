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

if __name__ == "__main__":
    
    integer = bin2int("1111111100000010")
    print("1111111100000010 converted to integer: ", integer)
    binary = int2bin(-254)
    print("-254 converted to binary: ", binary)
    binary = int2bin(254)
    print("254 converted to binary: ", binary)
