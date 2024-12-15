# PS1: Slide Puzzle Solver Version 1.1 10/3/2017 
# by Dr Loke K.S.
# based on Al Sweigart al@inventwithpython.com
# Released under a "Simplified BSD" license

from copy import deepcopy
import pygame, sys, random
from abc import ABCMeta, abstractmethod
from pygame.locals import *
import queue as Q
import pdb  #python debugger

#################
# Globals     ###
SIZE=3       #Size of the Puzzle, number of columns=number of rows
INITSTEPS=10   #Number of steps to scramble the puzzle at the start
start=[[1,4,7],[0,5,8],[2,3,6]]  #fixed starting position:must be same SIZExSIZE
SCRAMBLE=True    #if false then use the start[] data as starting position, 
                  #if true then scramble the tiles random for INITSTEPS times
#################

#
# Basic data structure Stack
#
#
class Stack:
     def __init__(self):
         self.items = []
     def isEmpty(self):
         return self.items == []
     def push(self, item):
         self.items.append(item)
     def pop(self):
         return self.items.pop()
     def peek(self):
         return self.items[len(self.items)-1]
     def size(self):
         return len(self.items)
#
# Basic data structure Queue
# (Use my own Queue instead of import) 
#        
class Queue:
    def __init__(self):
        self.items = []
    def isEmpty(self):
        return self.items == []
    def add(self, item):
        self.items.insert(0,item)
    def get(self):
        return self.items.pop()
    def size(self):
        return len(self.items)


#
# Solver Class: propose moves to the Board Class 
#
#
class Solver(metaclass=ABCMeta):
    """
     ABC=Abstract base class
     Abstract Solver class that searches through the state space, called by the Board class
    """
    @abstractmethod
    def get(self):
         raise NotImplementedError()
    @abstractmethod
    def add(self):
         raise NotImplementedError()
     
class Solver1(Solver):
    """
     Concrete solver: must implement abstract methods from abstract class Solver
     uses a Queue
    """
    def __init__(self):
        self.queue=Queue()
    def get(self):
        return self.queue.get()
    def add(self,board):
        self.queue.add(board)

class Solver2(Solver):
    """
     Concrete solver: must implement abstract methods from abstract class Solver
     Uses a Stack
    """
    def __init__(self):
        self.stack=Stack()
    def get(self):
        return self.stack.pop()
    def add(self,board):
        self.stack.push(board)

class Solver3(Solver):
    """
     Concrete solver 3: must implement abstract methods from abstract class Solver
     Uses the Python built-in Priority Queue
    """

    def __init__(self, goal,width,height):
        self.pq=Q.PriorityQueue()
        self.goal=goal
        self.w=width
        self.h=height
    def get(self):
        if not self.pq.empty():
             (val,board)=self.pq.get()
             return board
        else:
             return None
    def add(self, board):
        value=self.heuristic(board)
        self.pq.put((value,board))
    def heuristic(self,board):
        count=0;
        for x in range(self.w):
             for y in range(self.h):
                  if self.goal[x][y]!=board[x][y]:
                       count+=1
        return count
     
#  Board Class (Model): keep track on the abstract game state data. No animation or drawing
#                       methods. 
#
class Board:
    """Model class for the game that stores states about the game board.
       This class also include all the necessary operators.
       Does not handle Animation or screen processses.
    """
    BLANK=0
    
    UP = 'up'
    DOWN = 'down'
    LEFT = 'left'
    RIGHT = 'right'
    
    def __init__(self, bwidth, bheight):
        self.bwidth=bwidth
        self.bheight=bheight
        self.board=[]
        self.goal=[]
    
        # Initialize a board data structure with tiles in the solved state.
        # For example, if BWIDTH and BHEIGHT are both 3, this function
        # creates [[1, 4, 7], [2, 5, 8], [3, 6, BLANK]]
        # From the initial state we later scramble the positions to start the puzzle
        counter = 1
        for x in range(self.bwidth):
            column = []
            for y in range(self.bheight):
                column.append(counter)
                counter += self.bwidth
            self.board.append(column)
            counter -= self.bwidth * (self.bheight - 1) + self.bwidth - 1
        self.board[self.bwidth-1][self.bheight-1] = Board.BLANK
        self.goal=deepcopy(self.board)
    
       
        #### CHANGE THE SOLVER METHOD HERE ##
        #self.Solver=Solver1()
        #self.Solver=Solver2()
        self.Solver=Solver3(self.goal,bwidth,bheight)
        #####################################
               
    def solve(self): 
        #get board
        #get valid moves
        #put new board state in a data structure
        #repeat
        self.used=[]
        self.Solver.add(self.board)
        board=self.Solver.get()
        #pdb.set_trace()

        found=False
        while not(found):
            moves=self.getMoves(board)
            print("moves=",moves)
            for move in moves:
                print("trying ...",move)
                temp=self.makeMove(board,move)
                self.used.append(board)
                if not (temp in self.used):
                     self.printBoard(temp,"moved "+move)
                     self.Solver.add(temp)
                     #return [board, move]
                     if (temp==self.goal):
                          print("Found answer")
                          found=True
                          break
            board=self.Solver.get()
        return #[None,None]
 
    def printBoard(self, board, msg=None):
        print(msg)
        counter = 1
        for x in range(self.bwidth):
            for y in range(self.bheight):
               if board[y][x]==Board.BLANK:
                    print('X', end=' ')
               else:                       
                    print (board[y][x], end=' ')
            print()
        print()
        return
    
    def getBlankPosition(self,board):
        # Return the x and y of board coordinates of the blank space.
        for x in range(self.bwidth):
            for y in range(self.bheight):
                if board[x][y] == Board.BLANK:
                    return (x, y)
               
    def makeMove(self,original_board, move):
        # This function does not check if the move is valid.
        blankx, blanky = self.getBlankPosition(original_board)
        board=deepcopy(original_board)
        if move == Board.UP:
            board[blankx][blanky], board[blankx][blanky + 1] = board[blankx][blanky + 1], board[blankx][blanky]
        elif move == Board.DOWN:
            board[blankx][blanky], board[blankx][blanky - 1] = board[blankx][blanky - 1], board[blankx][blanky]
        elif move == Board.LEFT:
            board[blankx][blanky], board[blankx + 1][blanky] = board[blankx + 1][blanky], board[blankx][blanky]
        elif move == Board.RIGHT:
            board[blankx][blanky], board[blankx - 1][blanky] = board[blankx - 1][blanky], board[blankx][blanky]
        return board
            
    def isValidMove(self,board, move):
        blankx, blanky = self.getBlankPosition(board)
        return (move == Board.UP and blanky != len(board[0]) - 1) or \
           (move == Board.DOWN and blanky != 0) or \
           (move == Board.LEFT and blankx != len(board) - 1) or \
           (move == Board.RIGHT and blankx != 0)            

    def getMoves(self,board, lastMove=None):
        self.printBoard(board,"getMoves for .. ")
        
        # start with a full list of all four moves
        validMoves = [Board.UP, Board.DOWN, Board.LEFT, Board.RIGHT]
        # remove moves from the list as they are disqualified
        if lastMove == Board.UP or not self.isValidMove(board,Board.DOWN):
            validMoves.remove(Board.DOWN)
        if lastMove == Board.DOWN or not self.isValidMove(board,Board.UP):
            validMoves.remove(Board.UP)
        if lastMove == Board.LEFT or not self.isValidMove(board,Board.RIGHT):
            validMoves.remove(Board.RIGHT)
        if lastMove == Board.RIGHT or not self.isValidMove(board,Board.LEFT):
            validMoves.remove(Board.LEFT)

        # return a list of remaining moves
        return validMoves
    
    def getRandomMove(self,board, lastMove=None):
        # start with a full list of all four moves
        validMoves = [Board.UP, Board.DOWN, Board.LEFT, Board.RIGHT]
        # remove moves from the list as they are disqualified
        if lastMove == Board.UP or not self.isValidMove(board,Board.DOWN):
            validMoves.remove(Board.DOWN)
        if lastMove == Board.DOWN or not self.isValidMove(board,Board.UP):
            validMoves.remove(Board.UP)
        if lastMove == Board.LEFT or not self.isValidMove(board,Board.RIGHT):
            validMoves.remove(Board.RIGHT)
        if lastMove == Board.RIGHT or not self.isValidMove(board,Board.LEFT):
            validMoves.remove(Board.LEFT)

        # return a random move from the list of remaining moves
        return random.choice(validMoves)
    
    def scramble(self, num):
        lastMove=None
        for i in range(num):
            move = self.getRandomMove(self.board,lastMove)
            self.board=self.makeMove(self.board, move)
            lastMove=move
        self.printBoard(self.goal,"Goal")
        self.printBoard(self.board,"Start")


    
def main():
    game=Board(3,3)
    game.scramble(INITSTEPS)
    game.solve()

if __name__ == '__main__':
    main()
