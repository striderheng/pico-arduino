import io
from lib2to3.pgen2.token import NEWLINE
from PIL import Image
import numpy as np
import io
import os 

#set path to where the png files are
ospath = "G:/temp/epaperbmp/singles"
c_file = open("icons64x64.c", "w")
h_file = open("hfile_names.txt", "w")

def binarize_array(numpy_array, thresh):
    """Binarize a numpy array."""
    for i in range(len(numpy_array)):
        for j in range(len(numpy_array[0])):
            if (numpy_array[i][j]).any() > thresh:
                numpy_array[i][j] = 255  #255
            else:
                numpy_array[i][j] = 0
    return numpy_array


print(os.listdir(ospath))
for fname in os.listdir(ospath):
    #print(fname)
    fn_pre = fname.split(".")
    print(fn_pre[0])
    fname_csv = fn_pre[0]+"_CSV.txt"
    fname_txt = fn_pre[0]+".txt"
    print(fname_csv)
    temp = Image.open(ospath+"/"+fname)

#temp = Image.open("rain.png")

    thresh = 200
#fn = lambda x :255 if x > thresh else 0
    img = temp.convert('LA')
    #LA option(greyscale with chroma) gives a 3D array of which [:,:,0] gives what looks like a option L convert.
    # [:,:,1] suppose to give a chroma info which seems to show the icon properly

#img.show()
    #load PIL converted image into a numpy array(3D in this case)
    np_img = np.array(img)

    #the array of interest(don't know why) in the chroma array
    np_img_a = np_img[:,:,1]  
    np_img_a = ~np_img_a   #this gives a black background image, need to invert
    img_tp = Image.fromarray(np_img_a) #load it back into a SIL image array

    img_tp.show()

#np_img = ~np_img  # invert B&W
#np_img[np_img > 0] = 1

    #print(len(np_img))
    #print("np img: ",np_img.shape)
    #print("np img_a: ",np_img_a.shape)


#a_file = open("rain_csv.txt", "w")
    #create txt, CSV files and .c file
    #unsigned char image_64x64_rain_BW_mono[64][64]=
#{
    a_file = open(fname_csv, "w")
    b_file = open(fname_txt, "w")
    #c_file = open("icons64x64.c", "w")
    #for each icon setup the array declaration
    c_file.write("unsigned char image_64x64_" + fn_pre[0] + "_BW_mono[64][64]=\n")
    h_file.write("#define BW_" + fn_pre[0] + "_mono        (uint8_t *) & image_64x64_" + fn_pre[0] + "_BW_mono\n")
    c_file.write("{\n")
    for row in np_img_a:
        for item in row:
            tmp = str(item)
            if item.any() == 0:
                a_file.write("1,")
                c_file.write("1,")
                b_file.write("1")
            else:
                a_file.write("0,")
                c_file.write("0,")
                b_file.write("0")

        a_file.write("\n")   
        b_file.write("\n")
        c_file.write("\n")  

    a_file.close()
    b_file.close()
    c_file.write("};\n")
    c_file.write("\n") 

c_file.close()
h_file.close()         