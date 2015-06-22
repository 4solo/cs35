#!/usr/bin/python
import locale, sys
from optparse import OptionParser

class comm:
    def __init__(self, filename1,filename2):
        #if not stdin open file otherwise read stdin
        if filename1 is not sys.stdin:
            f = open(filename1, 'r')
            self.lines1 = f.readlines()
            f.close()
        else:
            f = filename1
            self.lines1 = f.readlines()
        if filename2 is not sys.stdin:
            f = open(filename2,'r')
            self.lines2 =f.readlines()
            f.close()
        else:
            f = filename2
            self.lines2 = f.readlines()

    def choosefile1(self):
        return self.lines1
    
    def choosefile2(self):
        return self.lines2
    
def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Compare sorted files FILE1 and File2 line by line."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                      action="store_true", dest="sup_1", default=False,
                      help="suppress column 1 (lines unique to FILE1)")
    parser.add_option("-2",
                      action="store_true", dest="sup_2", default=False,
                      help="suppress column 2 (lines unique to FILE2)")
    parser.add_option("-3",
                      action="store_true", dest="sup_3", default=False,
                      help="""suppress column 3 (lines that appear 
                      in both files)""")
    parser.add_option("-u",
                      action="store_true", dest="key_u", default=False,
                      help="""which causes comm to work even if 
                      its inputs are ot sorted.""")
    
    options, args = parser.parse_args(sys.argv[1:])

    input_file1 = args[0]
    input_file2 = args[1]
    if input_file1 == '-':
        input_file1 =sys.stdin
    if input_file2 == '-':
        input_file2 =sys.stdin
    #setlocale to C ;
    locale.setlocale(locale.LC_ALL,'C')
    try:
        generator = comm(input_file1,input_file2)
        list1=generator.choosefile1()
        list2=generator.choosefile2()
        if options.key_u :
            listsort1=sorted(list1,cmp=locale.strcoll)
            listsort2=sorted(list2,cmp=locale.strcoll)
        else :
            listsort1=list1
            listsort2=list2
        i=0
        commonlist=[]  #the list in common
        finallist=[]  #the list use for order
        w=0
        total=len(listsort1)+len(listsort2)
        #like merge sort for the sort list commpare  if there are the same
        #push into commonlist. if not u then output screen
        while i+w<total and i<len(listsort1) and w<len(listsort2):
             if listsort1[i]<listsort2[w] :
                 if not options.sup_1 and not options.key_u:
                     sys.stdout.write(listsort1[i])
                 i+=1
             elif listsort1[i]>listsort2[w] :
                 if not options.sup_2 and not options.key_u:
                     sys.stdout.write("\t"+listsort2[w])
                 w+=1
             else :
                 if not options.sup_3 and not options.key_u:
                     sys.stdout.write("\t\t"+listsort1[i])
                 commonlist.append(listsort1[i])
                 i+=1
                 w+=1
        #finish the rest part of the left it maybe for list 1 or list2
        while i<len(listsort1) and not options.sup_1:
            sys.stdout.write(listsort1[i])
            i+=1
        while w<len(listsort2) and not options.sup_2:
            sys.stdout.write(listsort2[w])
            w+=1
        j=0
        commonlist2=list(commonlist)
        #this due with the unorder list with u 
        while j<len(list1) and options.key_u:
            #print common thing base one list1 order
            if list1[j] in commonlist and not options.sup_3:
                sys.stdout.write("\t\t"+list1[j])
                commonlist.remove(list1[j])
                #print the one only in list 1 
            elif not list1[j] in commonlist and not options.sup_1:
                sys.stdout.write(list1[j])
            j+=1
        j=0
        while j<len(commonlist2):
            list2.remove(commonlist2[j])
            j+=1
        j=0
        #print the list 2 in the end
        while j<len(list2) and options.key_u:
            if not options.sup_2:
                 sys.stdout.write("\t"+list2[j])
            j+=1
    except IOError as err:
        errno, strerror = err.args
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
                                        
    
    
    
    
    

