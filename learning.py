
import random
import subprocess
#parameters
Actions = ["NS", "EW"]  
random_prob = 0.1
discount_factor = 0.9
number_of_loops = 500
Number_intersection = 4
learning_rate = 0.1
#------
Q_table = [{} for _ in range(Number_intersection) ]

def run_simulation():
    subprocess.run(["python", "traffic_simulation.py"])

def readstate():
    states = []
    with open("state.csv" , "r") as f:
        for line in f:
            ns , ew , emergency , adjacent_queue= line.strip().split(",")
            states.append((int(ns) , int(ew) , emergency , int(adjacent_queue)))
    return states

def queue_length(queue):
    if queue < 5:
        return "Low"
    elif queue >= 5 and queue < 10:
        return "Medium"
    else:
        return "High"
    
def adjacent_que(q):
    if q < 5:
        return "Low"
    elif q >= 5 and q < 10:
        return "Medium"
    else:
        return "High"
       
def build_states(raw_states):
    states = []
    for i in range(len(raw_states)):
      ns,ew,emergency_dir, adjacent_queue = raw_states[i] 
      states.append((queue_length(ns), queue_length(ew), emergency_dir, adjacent_que( adjacent_queue)))
    return states
    
def ensure_state(Q, state):
    if state not in Q:
        Q[state] = {"NS": 0.0 , "EW": 0.0}


def choose_action(Q,state):
    ensure_state(Q,state)
    ns , ew , emergency_dir , adjacent_queue = state

    if random.random() < random_prob:
    
        return random.choice(Actions)
    return max(Q[state], key = Q[state].get)

def write_actions(actions):
    with open("action.txt" , "w") as f:
        for i,action in enumerate(actions):
            f.write(f"{i} {action}\n")

def compute_rewards(ns , ew, emergency,  action,adjacent_queue):
    reward = -(ns+ew)
     
    if emergency != "NONE" and action != emergency:
        reward = reward-30
    if adjacent_queue =="High":
        reward = reward - 10
    return reward

def update_q(Q,state,action, reward, next_state):
    ensure_state(Q,next_state)
    best_next = max(Q[next_state].values())
    Q[state][action] += learning_rate * ( reward + discount_factor * best_next - Q[state][action])

#Main loop ---------------------------------------------------------------------------

for episode in range(number_of_loops):
    run_simulation()

    raw_states = readstate()
    states= build_states(raw_states)

    actions = []
    for i in range(Number_intersection):
        action = choose_action(Q_table[i] , states[i])
        actions.append(action)
    
    write_actions(actions)
    next_raw_states = readstate()
    next_states = build_states(next_raw_states)
    for i in range(Number_intersection):
        ns, ew , emergency, adjacent = raw_states[i]
        reward = compute_rewards( ns, ew , emergency , actions[i], adjacent)

        update_q(Q_table[i], states[i], actions[i], reward, next_states[i])

    if episode % 50 == 0:
        print(f"Episode {episode}")