count = 0
with open("chancesnowcoord.txt","r") as coordmap:
    for i in coordmap:
        print(i)
        if i == "\n":
            count = count + 1
coordmap.close()

print(count)

with open("rain.txt","r") as coordmap:
    for count, line in enumerate(coordmap):
        #print("line: ", type(line))
        each_line = enumerate(line)
        #foo = ([pos for pos, char in each_line if char == "1"])
        for pos, char in each_line:
            if char == "1":
                pixel_coord ="myScreen.point(" + str(pos) + "+offsetX, " + str(count) +"+offsetY, myColours.black);"
                print(pixel_coord)
        #print("line:", count, " in positions: ",foo)

        pass
print('Total Lines', count + 1)
coordmap.close()

