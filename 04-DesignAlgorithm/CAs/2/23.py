from itertools import combinations
n = int(input(""))
mountains = []
regular=n

mountains=list(map(int, input("".format(n)).split()))                    
combinationMountain = []
for r in range(1, len(mountains) + 1):
    combinationMountain.extend(combinations(mountains, r))

# يطبع جميع التركيبات
i=0
z1=0 
z2=0
for combination in combinationMountain:
          min=0
          max=len(combination)-1
          z1=0 
          z2=0
          l=len(combination)
          if (l%2==0 and l>1):
            
                for i in range(len(combination)-1):
                 
                        if(i<len(combination)):
                            if combination[i]<=combination[i+1] and i<=l/2:
                                z1+=1
                            if combination[i]>=combination[i+1] and i+1>=l/2:
                                z2+=1
                            if combination[max]==combination[min]:
                               max-=1
                               min+=1
                            if(z1==len(combination)/2 and z2==len(combination)/2 and min==len(combination)/2):
                               regular+=1     
          if (l%2!=0 and l>1):
                
                for i in range(len(combination)-1):
                 
                        if(i<len(combination)):
                            if combination[i]<=combination[i+1] and i<=l/2:
                                z1+=1
                            if combination[i]>=combination[i+1] and i+1>=l/2:
                                z2+=1
                            if combination[max]==combination[min] and min!=max:
                               max-=1
                               min+=1
                            if(z1==round(len(combination)/2)-1 and z2==round(len(combination)/2)-1 and min==round(len(combination)/2)-1):
                               regular+=1     



print(regular)                                          
