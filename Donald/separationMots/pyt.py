
import sets

liste = set()
liste.add('tutu')
fp = open('../Trumptweet','r')
lignes = fp.readlines()
fp.close()
for l in lignes:
    #try:
    liste.add(l.replace('\n',' '))
    #except:
        #print("erreur :"+l)
print(liste)
print(len(liste))