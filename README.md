# Stable Roommates Matching

This C++ program implements **Irving's Algorithm** to solve the **Stable Roommates Problem** for `n` individuals (where `n` is even). Each person ranks all others in order of preference, and the algorithm attempts to produce a stable matching where no two people would both prefer each other over their assigned partners.

Given `n` individuals (even number), each person provides a list of `n-1` preferences (all other individuals ranked in order). The goal is to find a **stable matching** — a pairing of individuals such that no unmatched pair of individuals would both prefer each other over their current partners.

## Phases in the Algorithm:

The implementation follows two main phases of Irving’s algorithm:

### Phase 1: Proposal Phase
- Each person proposes to others based on their preference list.
- If the person being proposed to prefers the proposer over their current consideration, they accept and reject the other.
- Rejected proposals are removed.
- At the end of this phase, each person should have exactly one active proposal.

### Phase 2: Rotation Elimination
- Identify **rotations** — cyclic sequences of individuals whose preferences can be safely eliminated.
- Remove these pairs from each other's lists.
- Repeat until all preference lists have exactly one individual or until some become empty (in which case no stable matching exists).

