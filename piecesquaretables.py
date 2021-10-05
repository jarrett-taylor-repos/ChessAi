f = open('makingpiecesquare.txt','r')

for line in f:
        message = ""
        for i in range(len(line)):
                message+=line[i]
        #print(message)
f = open('makingpiecesquare.txt','r')
for line in f:
        message = ""
        for i in range(len(line)-1,-1,-1):
                message+=line[i]
        print(message)


for i in range(5,1,-1):
        print(i)