//
//  main.cpp
//  stuffed bits signal
//
//  Created by Argyro on 25/6/21.
//

# stuffing the stuffed signal


def stuff(sig):
    onec = 0  # one counter
    c = 0   # index counter
    one = []  # one indexes
    s = list(sig)
    for i in s:
        c += 1
        if i == '0':
            onec = 0
        else:
            onec += 1
        if onec == 5:
            one.append(c)
            onec = 0
    k = 0  # count extra index number
    for i in one:
        # print(i)
        s.insert(i + k, '0')
        k += 1
    return s


# destuffing the stuffed signal
def destuff(sig):
    onec = 0  # one counter
    c = 0   # index counter
    one = []  # one indexes
    sig = list(sig)
    for i in sig:
        c += 1
        if i == '0':
            onec = 0
        else:
            onec += 1
        if onec == 5:
            one.append(c)
            onec = 0
    k = 0  # count extra index number
    for i in one:
        # print(i)
        sig.pop(i + k)
        k -= 1
    return sig


# ******************** Driver Code ************************* #
sig = input("Enter the signal: ")
print("Original Signal : ", sig)

stf = stuff(sig)
print("Stuffed Signal : ", end="")
print("".join([x for x in stf]))

dstf = destuff(stf)
print("Destuffed Signal : ", end="")
print("".join([x for x in dstf]))
