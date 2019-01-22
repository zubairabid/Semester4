# Simple Reflex Agents

## Simple Reflex Agent Architecture
 - Assumes knowledge of full state of the world


# Model based reflex agents
 
 - Handles partial observability (Allows agent to keep track of the part of the world it can't see)
 	- Maintain internal state that depends on percept history
 	- Eg: To change lane, we have to track rough positions

 - To Update internal information,
 	- We need info on how the world evolves independent of the agent
 	- We need to keep track of how the agent's actions affect the world

 - New state = UpdateState(Current Percept, Old Internal State)

 - New state is a best guess

 