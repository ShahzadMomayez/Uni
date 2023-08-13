#shahzad3


def move_robot(from_loc, robot,left_side,right_side) :
    if from_loc == 'Left' :
        if robot == 'L':
            left_side.remove('L')
            right_side= ['L']+ right_side
            
        elif robot == 'S':
            left_side.remove('S')
            right_side.append('S')

    elif from_loc =='Right':
       
        if robot == 'S' :
            right_side.remove('S')
            left_side.append('S')
        else:
            right_side.remove('L')
            left_side=['L']+ left_side
    return left_side,right_side
    

def print_ans (ans,step) :
    print ("Solution: " +str(step-1)) 
    print(ans)


def func(left_side,right_side , ans , step):
    
    while True:
        if 'S' not in right_side :
            left_side,right_side = move_robot( 'Left',  'S' ,left_side,right_side)
            left_side,right_side = move_robot( 'Left',  'S',left_side,right_side)
            ans= ans + "Action: Right\n"
            step = step+1
            ans = ans + "State"+str(step)+": " +str(left_side) + str (right_side) +'\n'
            if left_side != [] :
                left_side,right_side = move_robot( 'Right',  'S',left_side,right_side)
                ans= ans + "Action: Left\n"
                step = step+1
                ans = ans + "State"+str(step)+": " +str(left_side) + str (right_side) +'\n'
    
        else:
            if 'L' in left_side:
                left_side,right_side=move_robot( 'Left',  'L',left_side,right_side)
                ans= ans + "Action: Right\n"
                step = step+1
                ans = ans + "State"+str(step)+": " +str(left_side) + str (right_side) +'\n'
            elif 'L' not in left_side and left_side!=[]:
                left_side,right_side=move_robot( 'Left',  'S',left_side,right_side)
                left_side,right_side=move_robot( 'Left',  'S',left_side,right_side) 
                ans= ans + "Action: Right\n" 
                step = step+1
                ans = ans + "State"+str(step)+": " +str(left_side) + str (right_side) +'\n'
            if left_side!= [] :    
                left_side,right_side = move_robot('Right', "S",left_side,right_side)   
                ans= ans + "Action: Left\n" 
                step = step+1
                ans = ans + "State"+str(step)+": " +str(left_side) + str (right_side) +'\n' 
            if left_side==[] :
                return ans,step
                break

    
   
left_side =  ['L','L','S','S']
right_side = []
condition = True
action =[] 
step =1
ans="State"+str(step)+": " +str(left_side) + str (right_side) +'\n'
ans,step=func(left_side,right_side, ans, step)
print_ans(ans,step)

    