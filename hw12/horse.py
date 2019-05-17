
#initial call to make board and solve solution
def n_horses(n):
    b = make_board(n)
    result = solve(b, n*2, [])

    return result

#create board
# initialize values of the board with 0
def make_board(n):
    boards = []
    for i in range(n):
        boards.append([0 for j in range(n)])
        
    return boards


#recurse until all horses are positioned in the board
def solve(b, remaining_horses, positions):
    if remaining_horses == 0:
        #solution was solvable, print all the positions
        print(positions)
        return True

    #store entire board positions to open_spaces
    open_spaces = search(b)
    
    for candidate in open_spaces:
        if piece_placed(b, candidate, positions): #place horse in a position and continue with this choice
            if solve(b, remaining_horses-1, positions):
                return True #move successful
            unplace_piece(b, candidate, positions) #wrong move, undo



#searching through entire board
def search(b):
    q = []
    for row in range(len(b)):
        for spot in range(len(b)): 
                q.append((row,spot))
                          
    return q


#place horse in position b[x][y]
def piece_placed(b, candidate, positions):
    x = candidate[0] #row index
    y = candidate[1] #column index

    #place not possib;e
    if b[x][y] != 0:
        return False

    #update death points where other horses shouldn't be placed
    mark_deathpoints(b,x,y,val = 1)
    #add the current position
    positions.append(candidate)
    return True

#if a certain position doesn't work, undo move
def unplace_piece(b, candidate, positions):
    x = candidate[0]
    y = candidate[1]
     
     #subtract 1 in death points to get old value
    mark_deathpoints(b,x,y,val = -1)
    #remove the position
    positions.pop()
    return 


#checking if a horse could encounter a horse in all possible moves
#and updating values in positions where it would threaten another horse
def mark_deathpoints(b, x, y, val):
    b[x][y] += val

    x1, x2, x3, x4 = x+1, x-1, x+2, x-2
    y1, y2, y3, y4 = y+1, y-1, y+2, y-2

    if x1 < len(b) and y3 < len(b):
        b[x1][y3] += val

    if x1 < len(b) and y4 >= 0:
        b[x1][y4] += val

    if x2 >= 0 and y1 < len(b):
        b[x2][y1] += val

    if x2 >= 0 and y4 >= 0:
        b[x2][y4] += val

    if x3 < len(b) and y2 >= 0:
        b[x3][y2] += val

    if x3 < len(b) and y1 < len(b):
        b[x3][y1] += val

    if x4 >= 0 and y2 >= 0:
        b[x4][y2] += val

    if x4 >= 0 and y1 < len(b):
        b[x4][y1] += val

    return 


#main: ask user for n and execute
nu = int(input("Enter natural number: "))

if (n_horses(nu) != True):
    print("No solution exists!")
else:    
    print("are the positions of the horses in the board:")

