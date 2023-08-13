def find_min(i,j, arr ):
    if (j-i==0):
       return arr[i]

    elif (j-i==1):
        if(arr[i]>arr[j]):
            return arr[j]
        else:
            return arr[i]

    else:
        mid=int((i+j)/2)
        right_side=find_min(i, mid, arr)
        left_side=find_min(mid+1, j, arr)
        if(right_side>= left_side):
            return left_side
        else:
            return right_side


def find_index (number , arr):
    reverseArr= arr[::-1]
    for i in range(len(reverseArr)):
        if reverseArr[i] == number :
            value= len(arr) - 1 -i
            return value
            break



number_of_children = int(input())
arr=list(map(int, input(). strip(). split()))
i =0
j= len(arr) -1
min_value =find_min(i,j, arr )
min_index= find_index (min_value , arr)
ans = '(' + str(min_index) + ',' + str(min_value) + ')'
print(ans)