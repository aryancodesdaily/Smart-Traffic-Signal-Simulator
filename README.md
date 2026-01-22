# Smart-Traffic-Signal-Simulator

Smart Traffic Light Control Using Q-Learning
1. Problem Statement
Urban traffic congestion leads to excessive waiting times, fuel wastage, and delayed emergency
response. Conventional traffic lights operate on fixed or alternating timers (e.g., 30 seconds per
direction), which do not adapt to real-time traffic conditions. This results in inefficient signal usage,
especially during uneven traffic flow or emergency situations.
The goal of this project is to design an intelligent traffic signal control system that dynamically
decides which direction should receive the green signal based on real-time traffic conditions.
2. Proposed Solution Overview
The proposed solution uses Reinforcement Learning, specifically Q-learning, to make real-time
decisions for traffic signal control. The system learns from interaction with the traffic environment
and improves signal decisions over time.
The solution separates responsibilities between environment simulation and decision-making logic,
ensuring modularity and scalability.
3. Smart Traffic Light Control (Situation-Based)
Unlike traditional systems that alternate signals every fixed duration, this system makes decisions
based on the current situation. Factors such as queue length, emergency presence, and
downstream congestion are considered before switching signals.
This allows the signal to remain green longer for heavily congested directions and immediately
prioritize emergency vehicles when detected.
4. Average Waiting Time Optimization
Average waiting time is a key performance metric in traffic systems. It represents the mean time
vehicles spend waiting at the signal.
The learning agent aims to minimize the total queue length, which directly correlates with reducing
average waiting time. Lower queues result in faster vehicle clearance and smoother traffic flow.
5. Q-Learning Approach
Q-learning is a model-free reinforcement learning algorithm where an agent learns the quality
(Q-value) of actions taken in specific states.
In this project, the traffic state includes queue lengths and emergency information, while actions
correspond to selecting the green signal direction.
The agent updates its Q-values based on observed rewards, gradually learning an optimal traffic
signal policy.
6. System Architecture
The system consists of a C++ module that simulates the traffic environment and a Python module
that acts as the intelligent decision-making brain.
Both components communicate using simple file-based interfaces, ensuring language
independence and easy debugging.
7. Future Enhancements (To Be Updated)
The following features are planned for future versions of the system:
• • Multi-intersection traffic control
• • Handling complex emergency scenarios (multiple emergency vehicles)
• • Advanced reward functions
• • Integration with real-time sensors or cameras
Flowcharts and detailed diagrams will be added to visually represent system workflow and decision
logic.
8. Conclusion
This project demonstrates how reinforcement learning can be applied to intelligent traffic signal
control. By replacing fixed-time signals with a learning-based system, traffic efficiency is improved,
average waiting time is reduced, and emergency response is prioritized.