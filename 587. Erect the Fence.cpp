/*
Imagine you are walking around the fence 🚶‍♂️

Convex hull = walking around the outside boundary of all points.

You must walk in one continuous direction.

Step 1: Start from the leftmost point

You go:

LEFTMOST  →  RIGHTMOST


Along the bottom edge of the shape.

This is the lower hull.

You’re walking left → right.

✔️ Natural
✔️ No confusion
✔️ You always keep the points below you

Step 2: Now you must return to the start

You’re now at the rightmost point.

To complete the loop, you must walk back along the top edge.

There are only two choices:

❌ Wrong way

Go left → right again
You’d be walking inside the shape

✅ Correct way

Go right → left
So the outside stays on one side of your body

Key physical intuition 🧠

When you walk around an object, you don’t teleport — you reverse direction to come back.

Convex hull is a closed loop, not two independent lines.

Now the turning rule (this is the core)

While walking, you ask:

“Did I turn inward or outward?”

You must remove inward turns.

But:

What is “inward” depends on which way you’re walking

Lower hull intuition (left → right)

Picture this:

• —— • —— •


If the path bends downward, you went inside → ❌ remove
If it bends upward, you’re still outside → ✅ keep

So:

Bad turn = right turn

Remove it

Upper hull intuition (right → left)

Now you are walking backwards along the top.

Picture this:

• —— • —— •


From this direction:

A right turn still goes inside

A left turn stays outside

✨ Same logic works again ✨

Why not upper hull left → right?

Because then:

Your “inside” becomes “outside”

The same turn test starts deleting correct points

Geometry becomes inconsistent

You’d need different rules for upper and lower hull.

❌ Complicated
❌ Error-prone

Reversing direction = one universal rule

By reversing upper hull traversal:

while (bad turn) pop();


Works for:

lower hull

upper hull

Same logic
Same code
Same intuition

One sentence that locks it in 🔒

We reverse the upper hull so that “inside” always means the same turning direction while walking around the fence.

Final mental picture 🧠

Think of it like drawing with a pen ✏️:

Draw bottom edge → left to right

Without lifting pen, draw top edge → right to left

Remove any point that makes the line go inside

That’s it.
That’s the convex hull intuition.

If you want next:

I’ll explain this using a single bad example

Or show how deque one-pass hull works

Or explain why collinear points are special in this problem

Just tell me 👍

but why does it always work

This is the right question.
Once you ask “why does it always work”, you’re basically asking for the invariant of the convex hull algorithm.

Let’s lock that in.

The core invariant (this is the key)

At every step, the points stored form the convex hull of the points seen so far, in traversal order.

If this invariant is always true, the algorithm must end with the correct hull.

Now let’s see why it never breaks.

1️⃣ What does “wrong” even mean for a hull?

A point is wrong if:

It lies strictly inside the boundary formed by other points

Or it causes the boundary to bend inward

That’s it. There are no other failure modes.

So the algorithm only needs to:

Detect inward bends and remove them

2️⃣ Why the cross product detects inward bends (always)

Take three consecutive points in traversal order:

A → B → C


Two possibilities:

✅ Convex turn

The boundary keeps bulging outward
B must be on the hull

❌ Concave turn

The boundary bends inward
B is provably not extreme

This is not a heuristic — it’s geometry.

If B creates an inward turn, then segment AC encloses B, meaning:

B lies inside the polygon formed by A and C

So B cannot be on the convex hull. Ever.

That’s a mathematical guarantee.

3️⃣ Why removing B is always safe

This is the part people doubt.

“What if B becomes important later?”

It can’t.

Reason:

All future points are to the right (or left, depending on traversal)

If B is already inside triangle A–B–C

Adding more points cannot make B suddenly extreme again

Once a point becomes interior, it stays interior forever.

This is the monotonicity property.

4️⃣ Why traversal order makes this work

Sorting ensures:

x₁ ≤ x₂ ≤ x₃ ≤ ... ≤ xₙ


So:

We never “go backward”

New points only affect the end of the hull

The hull grows like a stack

That’s why a simple while(pop) loop works.

No revisiting old points.
No backtracking.
No global checks.

5️⃣ Why reversing the upper hull is essential (correctness, not convenience)

This is crucial.

The invariant requires:

“Inward” must always correspond to the same turn direction

If you don’t reverse:

Lower hull: inward = right turn

Upper hull: inward = left turn

❌ Two different rules
❌ Invariant breaks
❌ You’d need case logic

By reversing:

“Inward” = same cross-product sign everywhere

That’s why it always works — not by luck, but by design.

6️⃣ Why all hull points survive, always

Take any true hull point H.

Claim:

The algorithm will never pop H.

Why?

At H, the hull locally bends outward

So the turn is never inward

So the pop condition never triggers

Thus:

All extreme points stay

All interior points eventually get removed

This gives both soundness and completeness.

7️⃣ Why the final hull is guaranteed correct

At the end:

No inward turns remain

Boundary is fully convex

All points lie inside or on it

All extreme points are included

That exactly matches the definition of a convex hull.

The one-line proof intuition 🧠

The algorithm removes a point if and only if geometry proves it cannot be extreme, and such a point can never become extreme later.

That’s why it always works.


  */

class Solution {
public:
    
    int Equation(pair<int,int>& p1, pair<int,int>& p2, pair<int,int>& p3) {
    return (p2.first - p1.first) * (p3.second - p2.second)
         - (p2.second - p1.second) * (p3.first - p2.first);
}


    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        sort(trees.begin(),trees.end());
        deque<pair<int,int>>concave;//upper where m1 > m2
        deque<pair<int,int>>convex;//lower where m1 < m2
        int end=trees.size();
        if(end==1)return trees;


        for(int i=0,j=end-1;j>=0,i<end;i++,j--){
            vector<int>point=trees[i];
            pair<int,int>pnt={point[0],point[1]};
            int cave=concave.size();
            int vex=convex.size();
            //concave 
            while(cave >= 2 && Equation(concave[cave-1],concave[cave-2],pnt) < 0){
                concave.pop_back();
                cave--;
            }
            concave.push_back(pnt);
           
            //convex
             point=trees[j];
            pnt={point[0],point[1]};
            while(vex >= 2 && Equation(convex[vex-1],convex[vex-2],pnt) < 0){
                convex.pop_back();
                vex--;
            }
           

            convex.push_back(pnt);
        }
        vector<vector<int>>ans;
        set<pair<int,int>>res;
        for(int i=0;i<concave.size();i++){
            res.insert(concave[i]);
        }
        for(int i=0;i<convex.size();i++){
            res.insert(convex[i]);
        }
        vector<int>pnt(2,1);
        for(auto it:res){
            pnt[0]=it.first;
            pnt[1]=it.second;
            ans.push_back(pnt);
        }
        return ans;

    }
};
