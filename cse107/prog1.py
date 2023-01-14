"""*******************************************
	python code for project 1 in
	CSE 107 in 2022 winter, UC Santa Cruz,
			for Profw. Chen Qian.
**********************************************
	Student name: Shirin Rokni
	UCSC email: shrokni@ucsc.edu
"""

import numpy as np
import matplotlib.pyplot as plt
import simplerandom.iterators as sri

"""
Make a scatter plot of the distribution for these three RNG.
You'll generate num = 10,000 random number in range [0, num).
Make a single scatter plot using matplotlib with the x-axis being 
index of number and the y-axis being the number.

Hint(s):
    1. You'll call plt.scatter(...) for each rng. 
    Make sure your calls are of the form:
    'plt.scatter(x_vals, y_vals, c = 'b', s=2)' where c = 'b' indicates
    blue and s = 2 is to set the size of points. You may want to use
    "r", "g", and "b", a different color for each rng.
    2. Use plt.savefig(...).
"""

def distribution_random():
    np.random.seed(0)
    x_vals = np.arange(10000)
    y_vals = np.random.random(10000)
    plt.scatter(x_vals, y_vals, c = '#F8B195', s = 2)
    plt.xlabel("random number")
    plt.ylabel("index")
    plt.title("distribution_random")
    plt.savefig("plot1.png")
    plt.show()

def distribution_KISS():
    rng_kiss = sri.KISS(123958, 34987243, 3495825239, 2398172431)
    x_vals = np.arange(10000)
    y_vals = []
    for i in range(10000): 
        y_vals.append(next(rng_kiss) % 10000)

    plt.scatter(x_vals, y_vals, c = '#F67280', s = 2)
    plt.xlabel("random number")
    plt.ylabel("index")
    plt.title("distribution_KISS")
    plt.savefig("plot2.png")
    plt.show()

def distribution_SHR3():
    rng_shr3 = sri.SHR3(3360276411)
    x_vals = np.arange(10000)
    y_vals = []
    for i in range(10000):
        y_vals.append(next(rng_shr3) % 10000)

    plt.scatter(x_vals, y_vals, c = '#C06C84', s = 2)
    plt.xlabel("random number")
    plt.ylabel("index")
    plt.title("distribution_SHR3")
    plt.savefig("plot3.png")
    plt.show()
    



def pingpong(n:int=21, p:float=0.3, ntrials:int=5000, seed:int=0):
    """
    Write code to simulate a ping pong game to n points,
    where the probability of you winning a single point is p.
    You must win by 2; for example, if the score is 21 - 20, 
    the game isn't over yet. Simulate ntrials # of games.
    :param n: The number of points to play to.
    :param p: The probability of YOU winning a single point.
    :param ntrials: The number of trials to simulate.
    :return: returns the probability YOU win the overall game.
    You can ONLY use the function np.random.random() to generate randomness; 
    this function generates a random float from the interval [0, 1).
    """
    np.random.seed(seed)
    wins = 0

    def sim_one_game():
        #     """
        #     This is a nested function only accessible by parent sim_prob,
        #     which we're in now. You may want to implement this function!
        #     """
        # TODO: Your code here (10-20 lines)
        me = 0
        them = 0

        while True: 
            output = np.random.random()
            if output <= p:
                me += 1
            else: 
                them += 1
            
            if (me >= n) and ((me - them) >= 2):
                return True
            if (them >= n) and ((them - me) >= 2): 
                return False
        
    for i in range(ntrials):
        if sim_one_game():
            wins += 1

    return wins / ntrials


def plot_output():
    """
    Make a single plot using matplotlib with the x-axis being p
    for different values of p in {0, 0.04, 0.08,...,0.96, 1.0} 
    and the y-axis being the probability of winning the overall game 
    (use your previous function). Plot 3 "curves" in different colors, 
    one for each n in {3,11,21}.
    You can code up your solution here. Make sure to label your axes
    and title your plot appropriately, as well as include a 
    legend!
    Hint(s):
    1. You'll call plt.plot(...) 3 times total, one for each
    n. Make sure your calls are of the form:
    'plt.plot(x_vals, y_vals, "-b", label="n=11")' where "-b" indicates
    blue and "n=11" is to say these set of points is for n=11. You may 
    want to use "-r", "-g", and "-b", a different color for each n.
    2. Use plt.legend(loc="upper left").
    3. Use plt.savefig(...).
    :return: Nothing. Just save the plot you made!
    """
    
    # TODO: Your code here (10-20 lines)
    index = 0
    p = np.linspace(0.0, 1.0, 26) # a way of making a list from 0 to 1.0
    n_3 = np.zeros(26)
    n_11 = np.zeros(26)
    n_21 = np.zeros(26)

    for i in range(26): 
        n_3[i] = pingpong(3, index)
        n_11[i] = pingpong(11, index)
        n_21[i] = pingpong(21, index)
        index += 0.04

    plt.plot(p, n_3, color= '#FFCCFF', label = 'n = 3')
    plt.plot(p, n_11, color= '#FFCC66', label = 'n = 11', linestyle='--')
    plt.plot(p, n_21, color= '#FF99CC', label = 'n = 21',linestyle=':')
    plt.title("Relating P(win point) to P(win game)")
    plt.legend(loc="upper left")
    plt.xlabel("P(win point)")
    plt.ylabel("P(win game)")
    plt.savefig("pingpong.png")
    plt.show()

if __name__ == '__main__':
    # You can test out things here. Feel free to write anything below.
    distribution_random()
    distribution_KISS()
    distribution_SHR3()
    pingpong()
    plot_output()
