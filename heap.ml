type 'a heap = Leaf | Node of 'a * 'a heap * 'a heap

let empty = Leaf
let rec insert (h : 'a heap) (x : 'a) = match h with
    Leaf -> Node(x, Leaf, Leaf)
  | Node(v, l, r) -> Node(x, Leaf, Leaf);;

let insert (h : 'a heap) (x : 'a) = match h with
    Leaf -> Node(x, Leaf, Leaf)
  | Node(v, l, r) ->
    let c = compare x v in
    if c < 0 then if Random.bool()
      then Node(x, insert l v, r)
      else Node(x, l, insert r v)
    else if Random.bool()
      then Node(v, insert l x, r)
      else Node(v, l, insert r x);;

let rec merge (h1 : 'a heap) (h2 : 'a heap) = match h1, h2 with
    _, Leaf -> h1
  | Leaf, _ -> h2
  | Node(x1, l1, r1), Node(x2, l2, r2) ->
    let c = compare x1 x2 in
    if c < 0 then if Random.bool()
      then Node(x1, merge l1 h2, r1)
      else Node(x1, l1, merge r1 h2)
    else if Random.bool()
    then Node(x2, merge l2 h1, r2)
    else Node(x2, l2, merge r2 h1);;

exception Empty;;
let pop_min (h : 'a heap) = match h with
    Leaf -> raise Empty
  | Node(x, l, r) -> (x, merge l r);;
