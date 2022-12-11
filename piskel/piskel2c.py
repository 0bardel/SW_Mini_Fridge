import glob
import os
import sys
import codecs
import numpy as np
from PIL import Image
import re
from collections import defaultdict

#create output file
f = codecs.open("./menuBitmap.h", "w", "utf-8")


#Size of the output array. Array height is 8 times smaller than actual display size. 
arrayDimensions = (128,8)
arraySize = arrayDimensions[1]*arrayDimensions[0]




#get iterator of all gif files and iterate
for infile in glob.glob("*.gif"):
    #Open file
    with Image.open(infile) as im:
        #Comment
        f.write("//"+infile+"\n")
        #Get file name without the extension. Used for automatic naming of structs.     
        structName = os.path.basename(infile).lower().translate(str.maketrans(" ","_")).split(".")[-2]

        #Write array data. Append colors to palette as necessary.
        f.write("const char "+structName+'_data[{}]'.format(arraySize) + " = {" + "\n")

        #Set context to first frame
        im.seek(0)
        #Get RGB data as python list
        pixels = list(im.getdata().convert("RGB"))
        #Create array of color indexes.

        for ramPage in range(arrayDimensions[1]):
            f.write('\t')
            for col in range(arrayDimensions[0]):
                bin = 0;
                for i in range(0,8):
                    if pixels[ramPage*8*arrayDimensions[0] + col + i*arrayDimensions[0]] != (0,0,0):
                        bin += 2**i;
                f.write('0b'+format(bin,'b')+("," if (ramPage != arrayDimensions[1]-1 or col != arrayDimensions[0]-1) else ""))
            f.write('\n');
        f.write("};"+"\n")
f.close()
