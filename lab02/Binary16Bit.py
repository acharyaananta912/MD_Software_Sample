'''
This file consists two functions:
1. bin2int (it converts binary to decimal)
2. int2bin (it converts decimal to binary)
'''
def bin2int(bin_string):

    '''
    This function takes 16-bit binary number in Two's Complement representation 
    as a string and converts it to a decimal number.  
    '''
    
    # converts each elements of "bin_string" into integer and lists them
    bin_list = [int(x) for x in list(bin_string)] 

    # makes a multiplier for 16-bit Two's complement binary to decimal conversiont
    bin_to_dec_converter = [2**(x-1) for x in list(range(16,0,-1))]

    # Converts the first element of the binary multiplier to a negative number.
    bin_to_dec_converter[0] = -1*bin_to_dec_converter[0]

    # Elementwise multiplies the digits of input with a binary to conversion list and sums them all
    decimal = sum(list(map(lambda x,y: x * y, bin_list, bin_to_dec_converter)))

    return decimal


def int2bin(x):

    '''
    This function takes a integer and converts it to a 16-bit binary number in 
    Two's Complement representation as a string.
    '''
    # Empty list is initialized
    bin_string = [] 

    if x==0:

        # If input is 0, outputs 16 0s, i.e "000000000000"
        for n in range(0,16):
            bin_string.append("0")

    else:
        if x<0:
            tmp = "1"
            xmod = x + 2**15
        else:

            # if input is a positive number then the first digit of binary representation is set 0
            tmp = "0"
            xmod = x
        bin_string.append(tmp)
        
        for n in range(1,16):
            pw = 2**(15-n)
            z = int(xmod/pw)
            xmod = xmod - z*pw
            tmp = str(z)
            bin_string.append(tmp)

    bin_string = ''.join(bin_string)

    return bin_string

if __name__ == "__main__":
    
    decimal = bin2int("1111111100000010")
    print(decimal)
    binary = int2bin(-254)
    print(binary)
