## Control Engine

#### Connect each component with distributed and parallel message queue

- From GP to Control Engine: send `simulate` at port 7777 to trigger simulator
- From Control Engine: send `fitness` at port 7778
- From Local search to Control Engine: send `search` at port 7779
- From Control Engine to local search: send `fitness` at port 7780

#### Distribute mode (parallel execution to reduce evolution time) is on design