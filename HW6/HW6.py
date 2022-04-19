Input = open("input.txt", "r")
Output = open("output.txt", "w")

table = {}

for line in Input:
    word = line.split()
    if word[0] == "INSERT":
        key = word[1][4:len(word[1])]
        value = word[2][6:len(word[2])]

        if table.get(key) != None:
            Output.write("INSERT " + key + " FAIL!\n")
        else:
            table[key] = value
            Output.write("INSERT " + key + " SUCCESS!\n")

    elif word[0] == "FIND":
        key = word[1][4:len(word[1])]

        if table.get(key) == None:
            Output.write(key + " NOT FOUND!\n")
        else:
            Output.write("FIND " + key + ":" + table[key] + "!\n")
        
    elif word[0] == "ERASE":
        key = word[1][4:len(word[1])]

        if table.get(key) != None:
            table.pop(key)
            Output.write("ERASE " + key + " SUCCESS!\n")
        else:
            Output.write("ERASE " + key + " FAIL!\n")

    elif word[0] == "ENUM":
        lowkey = word[1][4:len(word[1])]
        highkey = word[2][4:len(word[2])]
        index1 = 0
        index2 = 0

        keylist = sorted(list(table.keys()))

        if table.get(lowkey) == None:
            index1 = 0
        else:
            index1 = keylist.index(lowkey)

        if table.get(highkey) == None:
            index2 = len(table) - 1
        else:
            index2 = keylist.index(highkey)

        for i in range(index1, index2 + 1):
            Output.write("ENUM " + keylist[i] + ":" + table[keylist[i]] + "\n")
        
    elif word[0] == "CLEAR":
        table.clear()

Input.close()
Output.close()