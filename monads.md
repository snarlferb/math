## Monads

*Note: Monoidal categories and monads from category theory are fundamentally different concepts, and I am mostly talking about monads here. I am also open to changing and/or stretching the rules of how they work to fit within the realms of the discussion.*

The monad structure in our case is the organized framework that holds our maturing thoughts, ensuring that for example: (A) Thoughts transform step by step (sequencing), and (B) Some parts can be prioritized while others are set aside but not lost (encapsulation). *Note, there's a good design example at the end*.

Steps in Thought Organization
- The monad (T) is the structured space that holds and transforms thoughts.
- Lifting (η) promotes raw ideas into the structure.
- Transforming (T(f)) applies reasoning and prioritization.
- Flattening (μ) or demoting the structure back to a single form so thoughts don’t become overly nested, and remain coherent.

Its not that different from writing down a priority tree/sub-tree, e.g. (3) TOPIC ATM —> then insert ┌---a sub level down —> ┌---and then another level down from that (where bb or minor subjects were written, that are to be promoted or demoted, depending on the previous level). Its the same sortve thing, but more clear as to what direction they go.

So theres **Monads for Analysis** and **Morphisms** (procedures). This is to address the monad part:
### Step 1: Raw Thought (RT)
We start with a vague question or idea: *"What are the factors influencing intelligence?"* (meaning from the non-algorithmic, scientific perspective)
Intelligence could be affected by: Biological, Environmental, Psychological and Random factors (luck, external events).
### Step 2: Lifting Into Structure (T(RT))
This step represent the re-prioritization/transformation of a sub-idea, adding or removing it from the above list of things, and we're bringing it into a structured thought process at the same time.
### Step 3: Refining Thought and Applying Priority (T(f))
We decide biological, environmental, and psychological factors are crucial. Random factors seem interesting, but for now, we tag them as NAP (Not A Priority) because they are less impactful for a structured theory (note: NAP is something I came up w/, so dont look for it on wikipedia)
### Step 4: Flattening (Final Understanding + Keeping NAP Aside)
We write down some of our findings (we dont have much to write for this example). We structure it like so:
- `T(Final Understanding)="Intelligence = Biology + Environment + Psychology"`
- `T(NAP)="Randomness might matter but is deprioritized."`

These could have been separate points (obstructing the maturation of each point), though they lean towards sequencing. Sequencing means that we process thoughts in a structured, logical order, ensuring that transformations happen step by step rather than all at once. Encapsulation means that when we process thoughts, we keep everything structured inside a monad, even if some elements are deprioritized.

Another way to think of it, is that we are *overloading function composition*, except we are overloading the actual raw data/ideas themselves.
### Morphisms composed over objects
The next part is about morphisms composed over objects. In the context of category theory, composition is a fundamental operation for morphisms (procedures w/ arrows)
When you have `f: A → B`, we say:
- `f` is a morphism from `A` to `B` (A and B which I just call objects)
- `A` is also the domain (or source) of `f`
- `B` is the codomain (or target) of `f`

There's also **directed composition**, that is a structured dependency where transformations must happen in a particular order, and objects may influence multiple targets at once. I like to illustrate them using two arrows, such as this:
```
B →^g1^→P,   E→^g2^→P,  P→^g3^→I
```
Transformations `g1` and `g2` are those dependencies that `B` depends on, in order to contribute to `P` (`B` and `E` which both contribute to `P`). These are relationships you would presumably have to write out first in order to know if such a complex relationship even exists, let alone what those transformational aspects are; A monad, of course being a context-aware transformation process, alas we exploit it to think of things/ideas monadically.


Morphisms are sometimes called maps or mappings as well. The notation `f: A → B` defines a single morphism `f` that goes from object `A` to object `B`.
When we talk about composition, we're referring to chaining these morphisms together, like `g ∘ f` which is a composition, wherein `f: A → B` and `g: B → C`—resulting in a new morphism from `A` to `C`.

An example of a composition is `g ∘ f`. Or rather, it represents the composition of morphisms `f` and `g`. If `f: A → B` and `g: B → C` are morphisms in a category, their composition `g ∘ f: A → C` (that is now a **morphism** that **results** from composition) is a new morphism from `A` to `C`. Composition must also be associative: `h ∘ (g ∘ f) = (h ∘ g) ∘ f`. And, every object `A` has an identity morphism `idₐ` such that `f ∘ idₐ = f` and `idₐ ∘ g = g`.

Heres some interesting properties to think about:
1. A monad on a category `C` is a triple (`T, η, μ`) meaning, it consists of three specific components:
   - `T: C → C` is an endofunctor
   - `η: Id → T` is the unit natural transformation (identity to `T`)
   - `μ: T² → T` is the multiplication natural transformation (`T` composed with itself to `T`)

2. The monad laws involve composition:
   - Left identity: `μ ∘ (η ∘ T) = idₜ`
   - Right identity: `μ ∘ (T ∘ η) = idₜ`
   - Associativity: `μ ∘ (μ ∘ T) = μ ∘ (T ∘ μ)`
### Monadic Structure Example
The Identity Monad simply wraps a value without any recursion: `T(X)=X`
Although when we think of monads, we see alot of recursive examples that, somehow, naturally generate multiple layers of monadic context `(T(T(X)))`. For example, a single function call isn’t recursive. But when you apply monadic structure to stateful computations, recursion naturally emerges—even if the underlying concept isn’t recursive at first.

Imagine a function that updates some state `S`. Given an input state, it produces a new state and an output:
```
f: S → (S,X)
```
Or we could also describe it as...
```
incrementM: S → (S,X)
```
A function tracking a counter in C might work like this:
```c
  int increment(int state) {
    return state + 1;
  }
```
Chaining two stateful computations in Haskell looks like:
```haskell
incrementM >>= incrementM
```
or in C-like pseudocode:
```c
int new_state = increment(old_state);
new_state = increment(new_state);
```
Instead of a single function (back in Haskell) we can dynamically chain arbitrary computations, where each step depends on the previous one:
```haskell
incrementM >>= incrementM >>= incrementM >>= ...
```
The first call produces a new state, the next call feeds that state into another computation, and this recursively threads state through each step. Even though incrementM itself is not recursive, the monadic composition rule (>>=) enforces a recursive structure.
### Whats the significance of this?
The monadic `>>=` automates state passing, ensuring that each step gets the correct updated state, and the process scales naturally (e.g., 100 increments). You also don’t have to manually pass the state each time.

Here's a more elaborate example in C, first w/ a loop, and then another example that just uses recursion instead:
```c
  int increment_n_times(int state, int times) {
    for (int i = 0; i < times; i++) {
        state = increment(state);
    }
    return state;
  }

  int increment(int state) {
    return state + 1;
  }

  int main() {
    int state = 3;
    int amount = 3;
    state = increment_n_times(state, amount);
    printf("%d\n", state);  // Output: 6
    return 0;
  }
```
`increment_n_times` applies `increment` `times` (that many times). The function abstracts away explicit manual calls. Instead of a loop, you can define it recursively too:
```c
  int increment_n_times(int state, int times) {
    if (times <= 0) return state;   // Base case: Stop when times is 0
    return increment_n_times(increment(state), times - 1);
  }
```
Again, we call `increment` recursively `times` (that many times). And, when `times == 0`, it stops. I suppose this is also a decent example of when you want to increment and/or call a function a certain amount of times, and dont want to manually call said function *over and over*.
