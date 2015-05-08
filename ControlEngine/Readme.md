## Control Engine

#### Connect each component with distributed and parallel message queue

- **[Done]** From GP to Control Engine: send `simulate` to `robocode_queue` to trigger simulator
- From Control Engine: send `fitness`
- From Local search to Control Engine: send `search`
- From Control Engine to local search: send `fitness`

#### Distribute mode (parallel execution to reduce evolution time) is on design