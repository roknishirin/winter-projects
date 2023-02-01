# =============================================================
# You may define helper functions, but DO NOT MODIFY
# the parameters or names of the provided functions.

# Do NOT add any import statements.
# =============================================================

import numpy as np
import simplerandom.iterators as sri

"""
The data for this problem is provided in pokemon.txt and follows the
following format.
Col 1: pokemon_id: A unique identifier for the Pokemon.
Col 2: is_legendary: A 1 if the Pokemon is legendary, and 0 otherwise.
Col 3: height: The height of the Pokemon in meters.
Col 4: weight: The weight of the Pokemon in kilograms.
Col 5: encounter_prob: The probability of encountering this Pokemon 
in the wild grass. Note the sum of this entire column is 1, since when
you make an encounter, exactly one of these Pokemon appears.
Col 6: catch_prob: Once you have encountered a Pokemon, the probability 
you catch it. (Ignore any mechanics of the actual game if you've played 
a Pokemon game in the past.)
"""

def part_a(filename:str='data/pokemon.txt'):
    """
    Compute the proportion of Pokemon that are legendary, the average
    height, the average weight, the average encounter_prob, and average 
    catch_prob. 
    :param filename: The path to the csv as described in the pset.
    :return: A numpy array of length 5 with these 5 quantities.
    Hint(s):
    1. Use np.genfromtxt(...) to load the file. Do NOT hardcode 
    'data/pokemon.txt' as the parameter as we may use other hidden
    files to test your function.
    2. Use np.mean(...) with its axis parameter to compute means in one line.
    """
    # TODO: Your code here (<= 3 lines)
    nums = np.genfromtxt(filename)
    return np.mean(nums, axis = 0)[1:]


def part_b(filename:str='data/pokemon.txt'):
    """
    Compute the proportion of Pokemon that are legendary, the average
    height, the average weight, the average encounter_prob, and average 
    catch_prob OF ONLY those Pokemon STRICTLY heavier than the median weight. 
    :param filename: The path to the csv as described in the pset.
    :return: A numpy array of length 5 with these 5 quantities.
    Hint(s):
    1. Use np.median(...) to compute medians along an axis.
    2. Use np.where(...) to select only certain rows.
    """
    pass # TODO: Your code here (<= 5 lines)
    nums = np.genfromtxt(filename)
    median_weight = np.median(nums, axis=0)[3]
    certain_rows = []
    for i in np.where(nums[ :,3] > median_weight)[0]:
        certain_rows.append(nums[i])
    output = np.mean(certain_rows, axis=0)
    return output[1:]

def part_c(filename:str='data/pokemon.txt', ntrials:int=5000):
    """
    Suppose you are walking around the wild grass, and you wonder: how
    many encounters do you expect to make until you ENCOUNTER each Pokemon 
    (at least) once? 
    :param filename: The path to the csv as described in the pset.
    :param ntrials: How many simulations to run.
    :return: The (simulated) average number of ENCOUNTERS you expect to 
    make, until you ENCOUNTER each Pokemon (at least) once.
    Hint(s):
    1. You only need to use one of the columns for this part!
    2. You may want to use np.random.choice(...) with the parameter a
    being np.arange(...) and the parameter p being the data column!
    """
    seed = 1
    np.random.seed(seed)
    nums = np.genfromtxt(filename)[:, 4]
    total = 0
    
    def sim_one():
        """
        This is a nested function only accessible by parent 'part_c',
        which we're in now. You may want to implement this function!
        """
        caught = []
        encounters = 0
        while (len(caught) < len(nums)):
            encounters += 1
            n = np.random.random()
            chance = 0
            index = 0
            for i in nums:
                chance += i
                index += 1
                if n < chance:
                    if index not in caught:
                        caught.append(index)
                    break                    
                else:
                    continue
        return encounters
                    
        

    # TODO: Your code here (10-20 lines)
    for i in range(ntrials):
        total += sim_one()
    return total / ntrials
    

def part_d(filename:str='data/pokemon.txt', ntrials:int=5000):
    """
    Suppose you are walking around the wild grass, and you wonder: how
    many encounters do you expect to make until you CATCH each Pokemon 
    (at least) once? 
    :param filename: The path to the csv as described in the pset.
    :param ntrials: How many simulations to run.
    :return: The (simulated) average number of ENCOUNTERS you expect to 
    make, until you CATCH each Pokemon (at least) once.
    Hint(s):
    1. You only need to use two of the columns for this part!
    2. You may want to use np.random.choice(...) with the parameter a
    being np.arange(...) and the parameter p being the data column!
    3. You may want to use np.random.rand(...).
    """
    data = np.genfromtxt(filename)[:, -2]
    catch_rate = np.genfromtxt(filename)[:, -1]
    n_pokemon = data.shape[0]
    seed = 1
    np.random.seed(seed)
    sum = 0

    def sim_one():
        """
        This is a nested function only accessible by parent 'part_d',
        which we're in now. You may want to implement this function!
        """
        caught = []
        catch = 0
        while (len(caught) < n_pokemon):
            catch += 1
            n = np.random.rand()
            chance = 0
            index = -1
            for i in data:
                chance += i
                index += 1
                if n < chance:
                    if index not in caught:
                        if (np.random.rand() < catch_rate[index]):
                            caught.append(index)
                    break                    
                else:
                    continue
        return catch
        
    
    # TODO: Your code here (10-20 lines)
    for i in range(ntrials):
        sum += sim_one()
    return (sum / ntrials)

if __name__ == '__main__':
    # You can test out things here. Feel free to write anything below.
    print(part_a())
    print(part_b())
    print(part_c())
    print(part_d())